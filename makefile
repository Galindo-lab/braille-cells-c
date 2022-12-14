
FLAGS = -W -Wall -std=c99 -c
FILE = main
EXEC = a.out


test: link
	./converter.out > output.txt

compile_o:
	gcc ${FLAGS} *.c

link: compile_o
	gcc -o converter.out *.o

clear:
	rm *.o



# compile_so:
# 	# https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html		
# 	gcc -c -Wall -Werror -fpic -std=c99 ${FILE}.c
# 	gcc -shared -o libtest.so ${FILE}.o	

