;;
;; Factorial program using while
;;

defun fact ; n on stack
1                 ; res
get_arg1       	  ; n

dup 0 lt     	  ; while (0 <= n) 

while
dup     ; res n n 
rot     ; n n res
*       ; n res
swap    ; res n
1       ; res n 1
swap    ; res 1 n
-       ; res (n-1)
dup 0 lt
endwhile
drop

return

;;
;; main function - note that this calls 2 procedures, print_int and endl that are
;; actually written in C
;;

defun main
4 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 4 on the ASCII display
5 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 5 on the ASCII display
6 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 6 on the ASCII display
7 set_arg1 fact set_arg1 print_int endl  ; print the factorial of 7 on the ASCII display
return 