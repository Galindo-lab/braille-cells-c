
FILE = main
EXEC = a.out
SOFILE = libtest

compile:
	gcc -W -Wall -std=c99 ${FILE}.c -o ${EXEC}
	if [ -f a.out ]; then ./${EXEC}; fi;
	if [ -f a.out ]; then rm ${EXEC}; fi;

compile_so:
	# https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html		
	gcc -c -Wall -Werror -fpic -std=c99 ${FILE}.c
	gcc -shared -o ${SOFILE}.so ${FILE}.o	

