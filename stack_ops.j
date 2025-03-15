;;
;; stack_ops.j
;;

defun main   
0x7000 0x0C00 + 50 dup + 10 30 - swap 40 drop 2 28 / swap 100 rot
set_arg1
set_arg2
set_arg3
set_arg4
print_quad
;; (0x7C00) (100) (20) swap (14) (100) rot
;; 0x7C00 20 100 14 100 rot
return