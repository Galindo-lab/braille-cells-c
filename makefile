
compile:
	# gcc -W -Wall -pedantic -std=c99 main.c
	gcc -W -Wall -std=c99 main.c
	if [ -f a.out ]; then ./a.out; fi;
	if [ -f a.out ]; then rm a.out; fi;

