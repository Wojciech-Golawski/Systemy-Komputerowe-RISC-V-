#ifndef PARAM
	#define PARAM
	#include <string.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <stdio.h>
	uint8_t * all_ptr;
	#define MEM_SIZE 1024*1024*16
	#define ADDR_CODE 		0x00000000
	#define SIZE_CODE		0x0000ffff
	#define ADDR_DATA_IN 	0x00010000
	#define SIZE_DATA_IN 	0x0000ffff
	#define ADDR_DATA_OUT 	0x00020000
	#define SIZE_DATA_OUT 	0x0000ffff
	#define IS_BIG_ENDIAN 0
	#define IS_BIG_ENDIAN2 0
	//#define MAX_IT_COUNT 1000000
	#define MAX_IT_COUNT 1000
	#define LOG(pos) printf("%5s pc=%4d: word=0x%.8X\n", pos, (*pc), word);
	//#define LOG(pos) 

#endif //PARAM
