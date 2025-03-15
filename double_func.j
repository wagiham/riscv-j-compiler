defun fact ; n on stack
get_arg1       	  ; n

dup 1 ge     	  ; n (1 >= n) 
if
   1 
else
   dup 1 swap -	  ; n (n-1)
   fact    	  ; n (n-1) (n-1)!
   swap drop * 	  ; n!
endif

return


defun fact_caller
get_arg1 fact
return 


defun main
4 set_arg1 fact_caller
0x00003300 swap dup 10 20
set_arg1 print_int drop
set_arg1 print_int drop
set_arg1 print_int drop
set_arg1 print_int drop
3 set_arg1 fact_caller
0x7A000000 swap dup 60 60
set_arg1 print_int drop
set_arg1 print_int drop
set_arg1 print_int drop
set_arg1 print_int drop
return

