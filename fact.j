;;
;; Factorial program
;;

defun fact ; n on stack
	get_arg1       	  ; n

	dup 1 ge     	  ; n (1 >= n) 
	if
   		1 
	else
   		dup 1 swap -	  ; n (n-1)
   		dup set_arg1 fact ; n (n-1) (n-1)!
   		swap drop * 	  ; n!
	endif

return

;;
;; main function - note that this calls 2 procedures, print_int and endl that are
;; actually written in C
;;

defun main
	4 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 4
	5 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 5
	6 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 6
	7 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 7
return 