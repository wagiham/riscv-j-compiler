#ifndef ASM_GEN_H 
#define ASM_GEN_H

#include <stdio.h>
#include <stdbool.h>
#include "token.h"  


void handle_arithmetic(token t, FILE* asm_file, FILE* input_file);
void temp_function(FILE* asm_file);
void handle_control_flow(token t, FILE* asm_file, FILE* j_file);


 #endif // COMPILER
