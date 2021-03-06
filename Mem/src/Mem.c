/*
===============================================================================
 Name        : Mem.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif



#include <cr_section_macros.h>

// TODO: insert other include files here

// TODO: insert other definitions and declarations here


#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#define MEM_BLOCK 200
#define POINTERS 40000 / MEM_BLOCK

void test_dynamicAllocation() {
    // Enough pointers to go over the 32k of memory.
    void * p[POINTERS];

    uint32_t used_memory = 0;
    uint32_t i = 0;

    /****************
     ** TEST Malloc.
     ****************/
    for (i = 0; i <POINTERS; i++) {
		p[i] = malloc(MEM_BLOCK);
		if (p[i]) {
			used_memory += MEM_BLOCK;
			memset(p[i], 0xAA, MEM_BLOCK);
		}
    }

    // Test free
    for (i = 0; i <POINTERS; i++) {
		if (p[i]) {
			free(p[i]);
			p[i] = NULL;
		}
    }
    used_memory = 0;


    /****************
     ** TEST calloc.
     ****************/
    for (i = 0; i <POINTERS; i++) {
		p[i] = calloc(1, MEM_BLOCK);
		if (p[i]) {
			used_memory += MEM_BLOCK;
			memset(p[i], 0xAA, MEM_BLOCK);
		}
    }

    // Test free
    for (i = 0; i <POINTERS; i++) {
		if (p[i]) {
			free(p[i]);
			p[i] = NULL;

		}
    }
    used_memory = 0;


    /****************
     ** TEST realloc with NULL pointer as first argument..
     ****************/
    for (i = 0; i <POINTERS; i++) {
		p[i] = realloc(p[i], MEM_BLOCK);
		if (p[i]) {
			used_memory += MEM_BLOCK;
			memset(p[i], 0xAA, MEM_BLOCK);
		}
    }

    // Test free
    for (i = 0; i <POINTERS; i++) {
		if (p[i]) {
			free(p[i]);
			p[i] = NULL;
		}
    }


    /****************
     ** TEST Test realloc, grow and shrink
     ****************/
    void * pointer = NULL;
    int grow = MEM_BLOCK;
    used_memory = grow;
    for (;;) {
		void * temp = realloc(pointer, used_memory);
		if (temp && used_memory != 0) {
			pointer = temp;
			memset(pointer, 0xAA, used_memory);
		} else {
			grow = grow * -1;
		}

		if (grow < 0 && used_memory <= MEM_BLOCK) {
			used_memory = 0;
		} else {
			used_memory += grow;
		}
    }

}



int main(void) {
	SystemCoreClockUpdate();
	test_dynamicAllocation();
    return 0 ;
}
