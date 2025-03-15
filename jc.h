#ifndef JC_H_
#define JC_H_

#include <stdio.h>
#include <stdlib.h>
#include "token.h"


FILE* open_file(const char *file_name, const char *mode);


void process_tokens(FILE *input_file, FILE *output_file);

#endif // JC_H_
