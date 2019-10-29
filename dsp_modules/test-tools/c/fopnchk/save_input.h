#include <stdio.h>
//
// extnpetrov@jabra.com
// syntax:
// save_input( device_address, dest_file, src1, src2, ..., srcn, 0);
// returns the bytes applied at device
// the genarated text file is compatible with the Keil debugger syntax.
// Use the debugger command:  "include _dest_filename" to apply the contain of the _dest_filename at _device address
// the structure of _dest_filename after applying in the device:
// src1 size, src1 data, src1 filename(aligned to 4), src2 size, src2 data, src2 filename(aligned to 4), ...., srcn size, srcn data, srcn filename(aligned to 4)
// 

#define SIMULATOR_ROM2_ADDRESS 0x20100000
// depends from the maximal length of the debugger command line
#define BYTES_PERLINE 0x100 // pow2

extern
#ifdef __cplusplus
extern "C"
#endif
int save_input(const unsigned int _device_address, const char* _dest_filename, ... /* _src_filenames */);
