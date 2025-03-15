all: jc

jc: jc.o token.o asm_gen.o
	clang-15 -g3 -gdwarf-4 -Wall -o jc jc.o token.o asm_gen.o

jc.o: jc.c token.h
	clang-15 -g3 -gdwarf-4 -Wall -c jc.c  

token.o: token.c token.h
	clang-15 -g3 -gdwarf-4 -Wall -c token.c

asm_gen.o: asm_gen.c asm_gen.h  token.h 
	clang-15 -g3 -gdwarf-4 -Wall -c asm_gen.c

clean:
	rm -f *.o jc 







