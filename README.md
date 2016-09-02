# ppmd_sh v9  by Eugene Shelwien.

ppmd_sh is a statistical compressor based on Dmitry Shkarin's ppmd vJr1 - see http://compression.ru/ds/

There's a benchmark: http://web.archive.org/web/20160729232814/http://compressionratings.com/i_ppmd.html

Basically ppmd is the only practical implementation of that method.
There were a few others, but they were severely limited by file size and had other quirks.
Also ppmd is fairly fast - its encoding is actually faster than lzma encoding, for example,
and at least text compression is much better at that.
But its a symmetric method, so decoding has the same speed while lzma is much faster.

Unfortunately, original source didn't provide a way to work with multiple codec instances at once
(lots of global variables), and had a fairly inefficient file i/o hardcoded in it, so large parts
of it ended up rewritten.
Unlike original, ppmd_sh codec is a normal object, and works as a coroutine - which means
that coding function returns to the caller with a status code asking to replace input or
output buffer, and then next call resumes the process. Thus, there's no need to write global
callback functions, or compress small blocks independently.

To compile: 
> g++ -O3 -s pmd.cpp -ILib -Ilibpmd -o pmd

To use: 
> Compress:   pmd c input_file output_file   
> Decompress: pmd d input_file output_file
 
Full commandline:
> pmd c/d input_file output_file [order] [memory] [reset_flag]
 
 Contacts: shelwien.san@gmail.com
