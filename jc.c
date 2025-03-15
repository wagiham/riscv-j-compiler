
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "asm_gen.h"
#include "token.h"

// void handle_token(token current_token, FILE* output_file);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
    return EXIT_FAILURE;
  }


  FILE* input_file = fopen(argv[1], "r");
  if (!input_file) {
    fprintf(stderr, "Error: Could not open input file '%s'\n", argv[1]);
    return EXIT_FAILURE;
  }

  char output_filename[FILENAME_MAX];
  strncpy(output_filename, argv[1], FILENAME_MAX - 3);
  output_filename[FILENAME_MAX - 3] = '\0';  

  char* dot = strrchr(output_filename, '.');
  if (dot) {
    strcpy(dot, ".s");
  } else {
    strcat(output_filename, ".s");
  }

  FILE* output_file = fopen(output_filename, "w");
  if (!output_file) {
    fprintf(stderr, "Error: Could not create output file '%s'\n",
            output_filename);
    fclose(input_file);
    return EXIT_FAILURE;
  }

  // Initialize token structure
  token current_token;
  //int label_counter = 0;
  //int useElse = 0;

  // Debug log
  // fprintf(stdout, "Processing tokens from '%s' to '%s'\n", argv[1],
  // output_filename);
  temp_function(output_file);
  // Read tokens from the input file and handle them
  while (next_token(input_file, &current_token)) {
    // fprintf(stdout, "Processing token: %s\n", current_token.str);
    
    if (current_token.type == IF) {
        printf("Entering conditional block\n");
        handle_control_flow(current_token, output_file, input_file);
    } else {
        handle_arithmetic(current_token, output_file, input_file);
    }

  }

  fclose(input_file);
  fclose(output_file);

//   fprintf(stdout, "Processing complete. Output written to '%s'\n",
//           output_filename);

  return EXIT_SUCCESS;
}
