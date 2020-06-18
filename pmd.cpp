
#define INC_FLEN
#include "common.inc"

enum { inpbufsize = 1<<16, outbufsize = 1<<16 };
ALIGN(4096) byte inpbuf[inpbufsize];
ALIGN(4096) byte outbuf[outbufsize];

uint pmd_args1[] = { 12, 256, 1, 0 };

#include "timer.inc"

void PrintInfo( FILE* f, FILE* g, uint iram, uint Mode ) {
  if( Mode ) { FILE* t=f; f=g; g=t; }
  double fn = ftell(f);
  double gn = ftell(g);
  float ram = iram;
  float bpb = fn>0 ? 8*gn/fn : 8;
  double tm = curtick-starttick; tm/=1000; 
  float sp = tm>0 ? fn/tm/1024 : 0;
  if( Mode ) { double t=gn; gn=fn; fn=t; } // SWAP( fn, gn );
  fprintf(stderr, " %.0lf > %.0lf, %4.2f bpb, %6.1fM RAM, %4.0fKb/s\r", fn,gn, bpb, ram/(1<<20), sp );
//  fflush(stdout);
}

#include "coro3b_fake.inc"
#include "libpmd/libpmd.inc"

ALIGN(4096) pmd_codec C;

uint f_DEC = 0;

int g_getc( FILE* f, FILE* g ) {
  static int g_block = 1000000;
  if_e0( --g_block<0 ) { CheckTimer(0); g_block=1000000; PrintInfo( f, g, C.GetUsedMemory(), f_DEC ); }
  return getc(f);
}

void g_putc( int c, FILE* f, FILE* g ) {
  putc( c, g );
}

int main( int argc, char** argv ) {

  if( argc<4 ) return 1;

  FILE* f = fopen(argv[2],"rb"); if( f==0 ) return 2;
  FILE* g = fopen(argv[3],"wb"); if( g==0 ) return 3;

  f_DEC = (argv[1][0]=='d');

  {
    int i;
    for( i=0; i<Min<int>(argc-4,DIM(pmd_args1)); i++ ) {
      char* p = argv[4+i]; p += (p[0]=='-');
      pmd_args1[i]=atoi(p);
    }
  }

  pmd_args1[3] = (f_DEC==0) ? flen(f) : -1;

  if( C.Init(f_DEC,pmd_args1) ) return 5;

C.f = f;
C.g = g;

  C.addout( outbuf, outbufsize );

  StartTimer();

  while(1) {
    if( CheckTimer(500) ) PrintInfo( f, g, C.GetUsedMemory(), f_DEC );

    uint l,r = C.coro_call(&C); //-V678
    if( r==1 ) {
      l = fread( inpbuf, 1, inpbufsize, f );
      C.addinp( inpbuf, l ); 
      if( l==0 ) C.f_quit=1;
    } else {
      l = C.getoutsize(); //C.outptr-C.outbeg; //C.getoutlen();
      fwrite( outbuf, 1, l, g );
      C.addout( outbuf, outbufsize );
      if( r!=2 ) break;
    }
  }

  BreakTimer();
  PrintInfo( f, g, C.GetUsedMemory(), f_DEC );
  printf( "\nProcessing time: " ); PrintTimer();
  printf( "\n" );

  C.Quit();

  fclose(f);
  fclose(g);

  return 0;
}

