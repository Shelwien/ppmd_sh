
struct Coroutine {
  uint f_quit;
  FILE* f;
  FILE* g;

  template <typename T> 
  uint coro_call( T* that ) {
    that->do_process();
    return 0;
  }

  void chkinp( void ) { }

  void chkout( uint d=0 ) {}

  uint get( void ) { return getc(f); }
  void put( uint c ) { putc(c,g); }

  void coro_init( void ) {
    f_quit=0;
  }

  uint getinplen() { return 0; } 
  uint getoutlen() { return 0; } 
  uint getinpleft() { return 0; }
  uint getinpsize() { return 0; }
  uint getoutleft() { return 0; }
  uint getoutsize() { return 0; }

  void addinp( byte* inp,uint inplen ) {}

  void addout( byte* out,uint outlen ) {}

  void yield( void* p, int value ) {}

};
