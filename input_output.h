#ifndef INPUT_OUTPUT
#define INPUT_OUTPUT

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

uint8_t * input(char * file_name, int * len_ptr);
uint8_t * inputb(char *file_name, int * len_ptr);
void output(char * file_name, uint8_t * data, int len);
void outputb(char * file_name, uint8_t * data, int len);
uint8_t zamiana_2x_char_na_hex(uint8_t starszy, uint8_t mlodszy);

#endif // INPUT_OUTPUT
