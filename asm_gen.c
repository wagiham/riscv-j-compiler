#include "asm_gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

int label_counter = 0;


// // Handling the 'literal' token
// void handle_literal(token t, Stack* stack, FILE* asm_file) {
//   // Push the literal value onto the stack
//   fprintf(asm_file, "    li x%d, %d\n", stack->top + 1, t.literal_value);
//   push_stack(stack, stack->top + 1);
// }
void temp_function(FILE* asm_file) {
  fprintf(asm_file, ".text\n");
  fprintf(asm_file, ".p2align 2\n");
}

// Handling arithmetic tokens
void handle_arithmetic(token t, FILE* asm_file, FILE* input_file) {
  switch (t.type) {
    case DEFUN: {
      next_token(input_file, &t);
      fprintf(asm_file, ".globl %s\n", t.str);
      fprintf(asm_file, "%s:\n", t.str);
      fprintf(asm_file, "    addi sp, sp, -8\n");
      fprintf(asm_file, "    sw ra, 4(sp)\n");
      fprintf(asm_file, "    sw fp, 0(sp)\n");
      fprintf(asm_file, "    addi fp, sp, 8\n");
      break;
    }
      // case RETURN:
      //  fprintf(asm_file, "    mv sp, fp \n");
      //  fprintf(asm_file, "   lw ra, -4(sp) \n");
      //  fprintf(asm_file, "    lw fp, -8(sp) \n");
      //  // fprintf(asm_file, "lw fp, 0(sp)\n");
      //  // fprintf(asm_file, "lw ra, 4(sp)\n");
      //  // fprintf(asm_file, "addi sp, sp, 8\n");
      //  // fprintf(asm_file, "jr ra\n");
      //  // logic for returning a value
      //  // follow up with a0, not the address that holds the return
      //  fprintf(asm_file, "ret\n");
      //  break;

    case RETURN:
      fprintf(asm_file,
              "    lw a0, 0(sp)    # Load return value into a0 (x10)\n");
      fprintf(asm_file, "    addi sp, sp, 4\n");
      fprintf(asm_file, "    mv sp, fp\n");
      fprintf(asm_file, "    lw ra, -4(sp)\n");
      fprintf(asm_file, "    lw fp, -8(sp)\n");
      fprintf(asm_file, "    jr ra\n");
      break;

    case PLUS:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    add t2, t1, t0  # t2 = t1 + t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case MINUS:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    sub t2, t0, t1  # t2 = t1 - t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case MUL:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    mul t2, t1, t0  # t2 = t1 * t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case MOD:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    rem t2, t1, t0  # t2 = t1 * t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case DIV:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    div t2, t0, t1  # t2 = t1 / t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;
    case AND:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    and t2, t1, t0  # t2 = t1 AND t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case OR:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    or t2, t1, t0   # t2 = t1 OR t0\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case NOT:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    not t2, t0  # t2 = NOT t0 (bitwise XOR with 1)\n");
      fprintf(asm_file, "    sw t2, 0(sp)  # Adjust stack pointer\n");
      break;

    case LT:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    slt t2, t0, t1  # t2 = (t1 < t0)\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case LE:
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    slt t2, t0, t1  # t2 = (t0 < t1)\n");
      fprintf(asm_file,
              "    seqz t2, t2     # t2 = !(t0 < t1) or (t0 >= t1)\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case EQ:  
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    sub t2, t1, t0  # t2 = t1 - t0\n");
      fprintf(asm_file, "    seqz t2, t2     # t2 = (t1 == t0)\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case GE:  
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n");
      fprintf(asm_file, "    lw t1, 4(sp)    # t1 = second item in stack\n");
      fprintf(asm_file, "    slt t2, t0, t1  # t2 = (t1 < t0)\n");
      fprintf(asm_file,
              "    seqz t2, t2     # t2 = !(t1 < t0) or (t1 >= t0)\n");
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case GT: 
      fprintf(asm_file, "    lw t0, 0(sp)    # t0 = top of stack\n"); 
      fprintf(asm_file,
              "    lw t1, 4(sp)    # t1 = second item in stack\n");  
      fprintf(asm_file, "    slt t2, t1, t0  # t2 = (t0 < t1)\n");   
      fprintf(asm_file, "    addi sp, sp, 4  # Adjust stack pointer\n");
      fprintf(asm_file, "    sw t2, 0(sp)    # Store result\n");
      break;

    case DROP:
      fprintf(asm_file, "    addi sp, sp, 4   # Drop the top item\n");
      break;

    case DUP:
      fprintf(asm_file, "    lw t0, 0(sp)     # Load the top item into t0\n");
      fprintf(asm_file, "    addi sp, sp, -4  # Move the stack pointer down\n");
      fprintf(asm_file,
              "    sw t0, 0(sp)     # Store t0 back onto the stack\n");
      break;
    case SWAP:
      fprintf(asm_file, "lw t0, 0(sp)\n");
      fprintf(asm_file, "lw t1, 4(sp)\n");
      fprintf(asm_file, "sw t1, 0(sp)\n");
      fprintf(asm_file, "sw t0, 4(sp)\n");
      break;

    case ROT:
      fprintf(asm_file, "lw t0, 0(sp)\n");
      fprintf(asm_file, "lw t1, 4(sp)\n");
      fprintf(asm_file, "lw t2, 8(sp)\n");
      fprintf(asm_file, "sw t2, 0(sp)\n");
      fprintf(asm_file, "sw t0, 4(sp)\n");
      fprintf(asm_file, "sw t1, 8(sp)\n");
      break;

    case GET_ARG:
      fprintf(asm_file, "    # Handle GET_ARG\n");
      fprintf(asm_file, "   addi sp, sp, -4 \n");
      fprintf(asm_file, "sw a%d, 0(sp)\n", t.arg_no - 1);
      break;
    

    case SET_ARG:
      fprintf(asm_file,
              "    lw t0, 0(sp)     # Load value from top of stack\n");
      fprintf(asm_file, "    addi sp, sp, 4   # Adjust stack pointer (pop)\n");
      fprintf(asm_file,
              "    mv a%d, t0       # Move value to argument register a%d\n",
              t.arg_no - 1, t.arg_no - 1);
      break;

    case LITERAL:
      fprintf(asm_file, "    # Handle LITERAL: %d\n", t.literal_value);
      fprintf(asm_file, "    li t0, %d       # Load literal value into t0\n",
              t.literal_value);
      fprintf(asm_file, "    addi sp, sp, -4  # Adjust stack pointer\n");
      fprintf(asm_file,
              "    sw t0, 0(sp)     # Store literal value on stack\n");
      break;

    case IDENT:
      fprintf(asm_file, "call %s\n", t.str);
      fprintf(asm_file, "addi sp, sp, -4\n");
      fprintf(asm_file, "sw x10, 0(sp)\n");
      break;

    case BAD_TOKEN:
      fprintf(asm_file, "    # BAD_TOKEN: Invalid token encountered: %s\n",
              t.str);
      fprintf(stderr, "Error: Invalid token encountered: %s\n", t.str);
      break;

    default:
      // printf("Unknown arithmetic operation\n");
      break;
  }
}

void handle_control_flow(token t, FILE* asm_file, FILE* j_file) {
  // bool useElse = false;
  //  declares an array named label that can hold a maximum of 200 characters.
  // static char label[200];
  // switch (t.type) {
  // case IF: {
  //   // keep track of a unique identifier for each label generated by the
  //   // compiler.
  //   int label_num = (*label_counter)++;
  //   // format a label string for the ELSE block within the
  //   handle_control_flow
  //   // function.
  //   snprintf(label, sizeof(label), "ELSE_%d", label_num);
  //   fprintf(asm_file,
  //           "    lw t0, 0(sp)    #Loads the condition value from the top
  //           of " "the stack into register t0.\n");
  //   fprintf(asm_file, "    addi sp, sp, 4  # Pop condition from
  //   stack\n"); fprintf(asm_file,
  //           "    beqz t0, %s    # Branch to ELSE if condition is
  //           false\n", label);
  //   break;
  //   // no labels are doubled,if, else -> make sure you dont execute else
  //   if
  //   // branch is false
  // }
  //   // beqz -> If the value in register t0 (the condition) is zero
  //   (false), it
  //   // branches to the ELSE label.
  //   // If the condition is true, the code continues to execute the block
  //   // following the if.

  // case ELSE: {
  //   // retrieve a label number for the ELSE block of an if statement
  //   int label_num = (*label_counter) - 1;
  //   // construct the label for the 'ENDIF' block w retrieved label
  //   number. snprintf(label, sizeof(label), "ENDIF_%d", label_num);
  //   // generate the assembly code to unconditionally jump to the 'ENDIF'
  //   // label.
  //   fprintf(asm_file, "    j %s          # Jump to ENDIF\n", label);
  //   // construct the label for the 'ELSE' block w retrieved label number.
  //   snprintf(label, sizeof(label), "ELSE_%d", label_num);
  //   // define the 'ELSE' label in the assembly code.
  //   fprintf(asm_file, "%s:\n", label);
  //   break;
  // }

  // case ENDIF: {
  //   int label_num = (*label_counter) - 1;
  //   snprintf(label, sizeof(label), "ENDIF_%d", label_num);
  //   fprintf(asm_file, "%s:\n", label);
  //   break;
  // }

  // case IF: {
  //   int label_num = (*label_counter)++;
  //   snprintf(label, sizeof(label), "ELSE_%d", label_num);
  //   fprintf(asm_file, "    lw t0, 0(sp)    # Load condition value\n");
  //   fprintf(asm_file, "    addi sp, sp, 4  # Pop condition from
  //   stack\n"); fprintf(asm_file,
  //           "    beqz t0, %s    # Branch to ELSE if condition is
  //           false\n", label);
  //   break;
  // }

  // case ELSE: {
  //   int label_num = (*label_counter)++;
  //   snprintf(label, sizeof(label), "ENDIF_%d", label_num);
  //   fprintf(asm_file, "    j %s          # Jump to ENDIF\n", label);
  //   snprintf(label, sizeof(label), "ELSE_%d", label_num - 1);
  //   fprintf(asm_file, "%s:\n", label);
  //   break;
  // }

  // case ENDIF: {
  //   int label_num = (*label_counter) - 1;
  //   snprintf(label, sizeof(label), "ENDIF_%d", label_num);
  //   fprintf(asm_file, "%s:\n", label);
  //   break;
  // }
  // case IF: {
  //   int label_num = (*label_counter)++;
  //   fprintf(asm_file, "    lw t0, 0(sp)    # Load condition value\n");
  //   fprintf(asm_file, "    addi sp, sp, 4  # Pop condition from
  //   stack\n"); fprintf(
  //       asm_file,
  //       "    beqz t0, ELSE_%d    # Branch to ELSE if condition is
  //       false\n", label_num);
  //   while (next_token) {
  //     if (t.type = ELSE) {
  //       useElse = true;
  //       fprintf(asm_file, "    j ENDIF_%d          # Jump to ENDIF\n",
  //               label_num);
  //       fprintf(asm_file, "ELSE_%d:\n", label_num - 1);  // Define ELSE
  //       label
  //     }
  //     if (t.type = ENDIF) {
  //       fprintf(asm_file, "ENDIF_%d:\n", label_num);     // Define ENDIF
  //       label
  //        if(useElse = true){ fprintf(asm_file, "ELSE_%d:\n",label_num -
  //        1);  // Define ELSE label
  //       }
  //     }
  //     // continue to parse if i hit else, endif,based on type
  //     // if its else, jump to here, or endif, jump to endif
  //     break;
  //   }

  // case ELSE: {
  //   int label_num = (*label_counter)++;
  //   break;
  // }

  // case ENDIF: {
  //   //dont decreme
  //   int label_num = (*label_counter) - 1;
  //   break;
  //   // whether we use else or not
  // }

  //  case IF: {
  //   int label_num = (*label_counter)++;
  //   bool useElse = false; // Track if an ELSE block exists

  //   fprintf(asm_file, "    lw t0, 0(sp)    # Load condition value\n");
  //   fprintf(asm_file, "    addi sp, sp, 4  # Pop condition from
  //   stack\n"); fprintf(
  //       asm_file,
  //       "    beqz t0, ELSE_%d    # Branch to ELSE if condition is
  //       false\n", label_num);

  //   // Parse subsequent tokens
  //   while (next_token(asm_file, &t)) {
  //       if (t.type == ELSE) {
  //           useElse = true;
  //           fprintf(asm_file, "    j ENDIF_%d          # Jump to
  //           ENDIF\n", label_num); fprintf(asm_file, "ELSE_%d:\n",
  //           label_num); // Define ELSE label
  //       } else if (t.type == ENDIF) {
  //           fprintf(asm_file, "ENDIF_%d:\n", label_num); // Define ENDIF
  //           label if (useElse) {
  //               fprintf(asm_file, "ELSE_%d:\n", label_num); // Ensure
  //               ELSE label exists
  //           }
  //           break;
  //       }
  //   }

  // case IF: {
  //   int label_num = (*label_counter)++;
  //   fprintf(asm_file, "    lw t0, 0(sp)    # Load condition value\n");
  //   fprintf(asm_file, "    addi sp, sp, 4  # Pop condition from stack\n");
  //   fprintf(
  //       asm_file,
  //       "    beqz t0, ELSE_%d    # Branch to ELSE if condition is false\n",
  //       label_num);
  //   break;
  // }

  // case ELSE: {
  //   int label_num = (*label_counter)++;
  //   fprintf(asm_file, "    j ENDIF_%d          # Jump to ENDIF\n",
  //   label_num); fprintf(asm_file, "ELSE_%d:\n", label_num - 1);  // Define
  //   ELSE label break;
  // }

  // case ENDIF: {
  //   int label_num = (*label_counter) - 1;
  //   fprintf(asm_file, "ENDIF_%d:\n", label_num);  // Define ENDIF label
  //   break;
  // }
  // when parsing control flow, loop through, handle_arithmetic,
  // if -> label counter
  // use same label counter for else,endif
  // after calling beqz
  // case IF: {
  //   if (t.type == IF) {
  //     (*label_counter)++;
  //     fprintf(asm_file, "    lw t0, 0(sp)        # Load condition value\n");
  //     fprintf(asm_file, "    addi sp, sp, 4      # Pop condition from
  //     stack\n"); fprintf(asm_file,
  //             "    beqz t0, SKIP_%d    # Branch to ELSE if condition is
  //             false\n", *label_counter);
  //   }
  // if (t.type == ELSE) {
  //     printf("Entering else block\n");
  //     *useElse = 1;
  //     // Emit jump to ENDIF and define ELSE label
  //     fprintf(asm_file, "    j ENDIF_%d          # Jump to ENDIF\n",
  //             *label_counter);
  //     fprintf(asm_file, "SKIP_%d:\n", *label_counter);  // Define ELSE label
  //   } else if (t.type == ENDIF) {
  //     printf("Entering ENDIF block\n");
  //     if (*useElse == 0) {
  //       fprintf(asm_file, "SKIP_%d:\n", *label_counter);
  //     } else {
  //       // Define the ENDIF label
  //       fprintf(asm_file, "ENDIF_%d:\n", *label_counter);
  //       (*label_counter)--;
  //     }
  //   }
  // while (next_token(asm_file, &t)) {
  //   int useElse = 0;
  //    //int label_counter = 0;
  //   if (t.type == IF) {
  //     label_counter++;
  //     int current_label = label_counter;
  //     fprintf(asm_file, "IF_%d:\n", label_counter);
  //     fprintf(asm_file, "    lw t0, 0(sp)        # Load condition value\n");
  //     fprintf(asm_file, "    addi sp, sp, 4      # Pop condition from  stack\n"); 
  //     fprintf(asm_file,
  //             "    beqz t0, SKIP_%d    # Branch to ELSE if condition is   false\n", current_label);
  //       // Handle nested IF blocks recursively
  //       while (next_token(asm_file, &t)) {
  //       if ((t.type == IF) || (t.type == ELSE) ||
  //           (t.type == ENDIF)) {
  //         handle_control_flow(t, asm_file);
  //       } // will this continue for else & end if?
  //     else if (t.type == ELSE) {
  //       fprintf(asm_file, "SKIP_%d:\n", label_counter);
  //       printf("Entering ELSE block\n");
  //       useElse = 1;

  //       // jump to ENDIF and define ELSE label
  //       fprintf(asm_file, "    j ENDIF_          # Jump to ENDIF\n");
  //       fprintf(asm_file, "SKIP_:\n");
  //     }
  //     else if (t.type == ENDIF) {
  //       printf("Entering ENDIF block\n");

  //       if (useElse == 0) {
  //         // Close IF without ELSE
  //         fprintf(asm_file, "SKIP_:\n");
  //       }
  //       // Define ENDIF label
  //       fprintf(asm_file, "ENDIF_:\n");
  //       return;
  //     }
  //     else {
  //       handle_arithmetic(t, asm_file, asm_file);
  //     }
  //   }
  // }
//   }
// }

    int useElse = 0;
    int current_label = label_counter++;
  if (t.type == IF) {
    fprintf(asm_file, "IF_%d:\n", label_counter);
    fprintf(asm_file, "    lw t0, 0(sp)        # Load condition value\n");
    fprintf(asm_file, "    addi sp, sp, 4      # Pop condition from stack\n");
    fprintf(asm_file,
            "    beqz t0, SKIP_%d    # Branch to ELSE if condition is false\n",
            current_label);

    // Process tokens inside the IF block
    while (next_token(j_file, &t)) {
       printf("check \n");
      if (t.type == IF) {
        printf("hello \n");
        // Handle nested IF blocks recursively
        handle_control_flow(t,asm_file, j_file);
      } else if (t.type == ELSE) {
        useElse = 1;
        fprintf(asm_file, "    j ENDIF_%d          # Jump to ENDIF\n",
                current_label);
        fprintf(asm_file, "SKIP_%d:\n", current_label);  // Define ELSE label
        while (next_token(j_file, &t)) {
          if (t.type == IF) {
            handle_control_flow(t, asm_file, j_file);  // Handle nested IF inside ELSE
          } else if (t.type == ENDIF) {
            break;
          } else {
            handle_arithmetic(t, j_file, asm_file);
          }
        }
        break;
      } else if (t.type == ENDIF) {
        fprintf(asm_file, "SKIP_%d:\n", current_label);
        break;
      } else {
        handle_arithmetic(t, j_file, asm_file);
      }
    }
    if (!useElse) {
      fprintf(asm_file, "SKIP_%d:\n", current_label);
    }
    fprintf(asm_file, "ENDIF_%d:\n", current_label);
  }
}

// If no ELSE block exists, define an ELSE label for continuity
// if (!useElse) {
//   useElse = true;
//     fprintf(asm_file, "SKIP_%d:\n", label_num);
// }

