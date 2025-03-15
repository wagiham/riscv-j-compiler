;;
;; Simple j program
;;

defun square ; called with parameter n
get_arg1   ;  n
dup *  ; (n*n)
return

defun main
4 set_arg1 square set_arg1 print_int endl ; print 4 squared
5 set_arg1 square set_arg1 print_int endl ; print 5 squared
return
