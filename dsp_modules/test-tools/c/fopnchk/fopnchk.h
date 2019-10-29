#include <stdio.h>
#include <stdlib.h>

// Simple file open with included check.
// Using this makes more readable code, and gives better error handling
// Written by Kristoffer Jensen

// for fopnchk_close_all we need to know the max number of file handles
#define FOPNCHK_BOOKKEEPING_LIMIT 100
/** @note There is a FOPEN_MAX define in <stdio.h> that seems to set
 *        the limit for how many files can be opened. Xtensa sets FOPEN_MAX
 *        to 20, and mingw32-g++ to 200.
 * */


FILE* fopnchk(const char *fname, const char *rwstr);
void fopnchk_close_all();
