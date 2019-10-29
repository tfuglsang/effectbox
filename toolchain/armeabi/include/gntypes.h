/* --------------------------------------------------------------------
 *
 *  GGGGGG  NN    N
 *  G       N N   N
 *  G  GGG  N  N  N - Netcom
 *  G    G  N   N N
 *  GGGGGG  N    NN
 *
 *  Copyright (c) 2006, GN-Netcom
 * -------------------------------------------------------------------- */

/**
 * @file gntypes.h
 * @brief Compiler specific header for system types and definitions
 *
 */

#ifndef __GNTYPES_H__
#define __GNTYPES_H__

#include <stdint.h>
#include <stdbool.h>

/* GCC specific pack syntax */
#ifndef PACKED
#define PACKED
#define PACKED_ATTR __attribute__((__packed__))
#endif
#define PRIVATE static

#define GN_NO_INIT(variable) variable __attribute__((section("NO_INIT.__LINE__" )))
/* Pointers are 32bit wide on most PC systems */
/* typedef uint32_t uintptr_t; */
#undef true
#define true 1
#undef false
#define false 0

#undef TRUE
#define TRUE 1
#undef FALSE
#define FALSE 0

#define CHAR_BITS 8
#endif /* __GNTYPES_H__ */

