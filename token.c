
#include "token.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int line_number = 1;  // Global variable for tracking line numbers

int skip_whitespace_and_comments(FILE* j_file) {
  int ch;
  while ((ch = fgetc(j_file)) != EOF) {
    if (ch == ';') {
      while ((ch = fgetc(j_file)) != '\n' && ch != EOF) {
        // Skip comment content
      }
      line_number++;  // Increment line number for newline
    } else if (!isspace(ch)) {
      return ch;  
    } else if (ch == '\n') {
      line_number++;  // Increment line number for newline
    }
  }
  return EOF;  // Return EOF if end of file is reached
}

bool next_token(FILE* j_file, token* output) {
  if (!j_file || !output) {
    return false;
  }

  memset(output->str, 0, sizeof(output->str));

  // Skip whitespace and comments
  int c = skip_whitespace_and_comments(j_file);
  if (c == EOF) {
    return false;  // End of file
  }


  output->str[0] = c;
  int i = 1;


  while (i < MAX_TOKEN_LENGTH && (c = fgetc(j_file)) != EOF && !isspace(c)) {
    output->str[i++] = c;
  }
  output->str[i] = '\0'; 

 
  if ((isdigit(output->str[0])) ||
      (output->str[0] == '-' && isdigit(output->str[1])) ||
      (output->str[0] == '0' &&
       (output->str[1] == 'x' || output->str[1] == 'X'))) {
    char* endptr;
    output->literal_value = strtol(
        output->str, &endptr, 0);  


    if (*endptr == '\0') {
      output->type = LITERAL;
    } else {
      output->type = BAD_TOKEN; 
    }
  } else if (strcmp(output->str, "defun") == 0) {
    output->type = DEFUN;

  } else if (strcmp(output->str, "return") == 0) {
    output->type = RETURN;
  } else if (strcmp(output->str, "+") == 0) {
    output->type = PLUS;
  } else if (strcmp(output->str, "-") == 0) {
    output->type = MINUS;
  } else if (strcmp(output->str, "*") == 0) {
    output->type = MUL;
  } else if (strcmp(output->str, "/") == 0) {
    output->type = DIV;
  } else if (strcmp(output->str, "%") == 0) {
    output->type = MOD;
  } else if (strcmp(output->str, "and") == 0) {
    output->type = AND;
  } else if (strcmp(output->str, "or") == 0) {
    output->type = OR;
  } else if (strcmp(output->str, "not") == 0) {
    output->type = NOT;
  } else if (strcmp(output->str, "<") == 0) {
    output->type = LT;
  } else if (strcmp(output->str, "lt") == 0) {
    output->type = LT;
  } else if (strcmp(output->str, "<=") == 0) {
    output->type = LE;
  } else if (strcmp(output->str, "le") == 0) {
    output->type = LE;
  } else if (strcmp(output->str, "=") == 0) {
    output->type = EQ;
  } else if (strcmp(output->str, "eq") == 0) {
    output->type = EQ;
  } else if (strcmp(output->str, ">=") == 0) {
    output->type = GE;
  } else if (strcmp(output->str, "ge") == 0) {
    output->type = GE;
  } else if (strcmp(output->str, ">") == 0) {
    output->type = GT;
  } else if (strcmp(output->str, "gt") == 0) {
    output->type = GT;
  } else if (strcmp(output->str, "if") == 0) {
    output->type = IF;
  } else if (strcmp(output->str, "else") == 0) {
    output->type = ELSE;
  } else if (strcmp(output->str, "endif") == 0) {
    output->type = ENDIF;
  } else if (strcmp(output->str, "while") == 0) {
    output->type = WHILE;
  } else if (strcmp(output->str, "endwhile") == 0) {
    output->type = ENDWHILE;
  } else if (strcmp(output->str, "drop") == 0) {
    output->type = DROP;
  } else if (strcmp(output->str, "dup") == 0) {
    output->type = DUP;
  } else if (strcmp(output->str, "swap") == 0) {
    output->type = SWAP;
  } else if (strcmp(output->str, "rot") == 0) {
    output->type = ROT;
  } else if (strncmp(output->str, "get_arg", 7) == 0) {
    output->type = GET_ARG;
    sscanf(output->str + 7, "%d", &output->arg_no); 
  } else if (strncmp(output->str, "set_arg", 7) == 0) {
    output->type = SET_ARG;
    sscanf(output->str + 7, "%d", &output->arg_no);  

  } else {
    bool is_valid_ident = true;
    for (int i = 0; output->str[i] != '\0'; i++) {
      if (!isalnum(output->str[i]) && output->str[i] != '_') {
        is_valid_ident = false;
        break;
      }
    }

    if (is_valid_ident) {
      output->type = IDENT;
    } else {
      output->type = BAD_TOKEN;
    }
  }

  return true;
}


void print_token(FILE* f, token to_print) {
  switch (to_print.type) {
    case DEFUN:
      fprintf(f, "DEFUN\n");
      break;
    case IDENT:
      fprintf(f, "IDENT: %s\n", to_print.str);
      break;
    case RETURN:
      fprintf(f, "RETURN\n");
      break;
    case LITERAL:
      fprintf(f, "LITERAL: %d\n", to_print.literal_value);
      break;
    case PLUS:
      fprintf(f, "PLUS\n");
      break;
    case MINUS:
      fprintf(f, "MINUS\n");
      break;
    case MUL:
      fprintf(f, "MUL\n");
      break;
    case DIV:
      fprintf(f, "DIV\n");
      break;
    case MOD:
      fprintf(f, "MOD\n");
      break;
    case AND:
      fprintf(f, "AND\n");
      break;
    case OR:
      fprintf(f, "OR\n");
      break;
    case NOT:
      fprintf(f, "NOT\n");
      break;
    case LT:
      fprintf(f, "LT\n");
      break;
    case LE:
      fprintf(f, "LE\n");
      break;
    case EQ:
      fprintf(f, "EQ\n");
      break;
    case GE:
      fprintf(f, "GE\n");
      break;
    case GT:
      fprintf(f, "GT\n");
      break;
    case IF:
      fprintf(f, "IF\n");
      break;
    case ELSE:
      fprintf(f, "ELSE\n");
      break;
    case ENDIF:
      fprintf(f, "ENDIF\n");
      break;
    case WHILE:
      fprintf(f, "WHILE\n");
      break;
    case ENDWHILE:
      fprintf(f, "ENDWHILE\n");
      break;
    case DROP:
      fprintf(f, "DROP\n");
      break;
    case DUP:
      fprintf(f, "DUP\n");
      break;
    case SWAP:
      fprintf(f, "SWAP\n");
      break;
    case ROT:
      fprintf(f, "ROT\n");
      break;
    case GET_ARG:
      fprintf(f, "GET_ARG: %d\n", to_print.arg_no);
      break;
    case SET_ARG:
      fprintf(f, "SET_ARG: %d\n", to_print.arg_no);
      break;
    case BAD_TOKEN:
      fprintf(f, "BAD_TOKEN\n");
      break;
    default:
      fprintf(f, "UNKNOWN TOKEN\n");
  }
}
