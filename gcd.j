;;
;; gcd - Compute the greatest common divisor of two numbers using the Eucldiean algorithm
;;

defun gcd  ;  arguments - b, a
get_arg2   ;  b, a, RV, RA, FP, b
0 eq   	   ;  b, a, RV, RA, FP, (b == 0)
if   
get_arg1   ;  b, a, RV, RA, FP, a
else
get_arg2   ;  b, a, RV, RA, FP, b
get_arg1   ;  b, a, RV, RA, FP, b, a
% 	   ;  b, a, RV, RA, FP, (a % b)
get_arg2   ;  b, a, RV, RA, FP, (a % b), b
set_arg1
set_arg2
gcd        ;  b, a, RV, RA, FP, gcd(b, (a % b))
endif
return


;;
;; main function - note that this calls 2 procedures, print_int and endl that are
;; actually written in C
;;

defun main
462 1071 set_arg1 set_arg2 gcd set_arg1 print_int endl ; print the gcd of 1071 and 462 which should be 21
return
