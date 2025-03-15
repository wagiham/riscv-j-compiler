;;
;; Very basic test - no ifs or comparisons
;;

defun main
5 3 2 * + set_arg1 print_int endl	;; Should output (3 * 2) + 5 = 11
3 4 5 rot * + set_arg1 print_int endl	;; Should output (3 * 5) + 4 = 19
return


