;;
;; Simple program that uses print functions and while
;;


;;
;; main function - note that this calls 2 procedures, print_int and endl that are
;; actually written in C
;;

defun main
5
dup
  while
  dup set_arg1 print_int endl drop drop
  1 swap -
  dup
endwhile

return 