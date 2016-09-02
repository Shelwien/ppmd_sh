# ppmd_sh v9  by Eugene Shelwien.

ppmd_sh is a statistical compressor based on Dmitry Shkarin's ppmd vJr1 - More details here : http://compressionratings.com/i_ppmd.html

Basically ppmd is the only practical implementations of that method.
There were a few others, but they were severely limited by file size and had other quirks.
Also ppmd is fairly fast - its encoding is actually faster than lzma encoding, for example,
and at least text compression is much better at that.
But its a symmetric method, so decoding has the same speed while lzma is much faster.


