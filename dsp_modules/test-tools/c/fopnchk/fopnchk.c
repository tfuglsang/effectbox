#include <stdio.h>
#include <stdlib.h>
#include "fopnchk.h"

// Helper program to open and check status
// Written by Kristoffer Jensen

// book keeping for close_all
static FILE * open_files[FOPNCHK_BOOKKEEPING_LIMIT];
static int number_of_open_files = 0;

// open a file
FILE* fopnchk(const char *fname, const char *rwstr) {                                                                   // Helper function for more readable code and better error handling
  FILE* ftmp=fopen(fname, rwstr);
  if (!ftmp) {
    printf("Error opening %s\n", fname);
    fopnchk_close_all();
    exit(-1);
  } else {
    if (number_of_open_files<FOPNCHK_BOOKKEEPING_LIMIT) open_files[number_of_open_files++] = ftmp;
  }
  return ftmp;
}

// close all open files
void fopnchk_close_all() {
  for (int i=0; i<number_of_open_files; i++) fclose(open_files[i]);
  number_of_open_files = 0;
}
