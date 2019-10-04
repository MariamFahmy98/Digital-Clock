/*
 * standard_types.h
 *
 *  Created on: Oct 4, 2019
 *      Author: marim
 */

#ifndef STANDARD_TYPES_H_
#define STANDARD_TYPES_H_

#define NULL (void*)0
typedef unsigned char bool;
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short uint16;
typedef signed short sint16;
typedef unsigned long uint32;
typedef signed long sint32;
typedef unsigned long long uint64;
typedef signed long long sint64;
typedef float float32;
typedef double float64;


#endif /* STANDARD_TYPES_H_ */
