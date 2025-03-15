;;
;; final.j
;;

defun times_5
get_arg1
5 *
return

defun half
2 get_arg1 /
return

defun plus_50
get_arg1 50 +
return

defun main   
0x7C0000 20 set_arg1 times_5 100 14
set_arg1 print_int drop endl drop
set_arg1 print_int drop endl drop
set_arg1 print_int drop endl drop
set_arg1 print_int drop endl drop
return
