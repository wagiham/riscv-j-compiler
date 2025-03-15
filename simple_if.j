;;
;; simple_if.j
;;

defun main
5 5 eq
if
0x7C00 20 100 100 14 
set_arg1
set_arg2
set_arg3
set_arg4
print_quad endl drop drop
else
0x7FF0 20  20  20 54
set_arg1
set_arg2
set_arg3
set_arg4
print_quad drop endl drop
endif
return

