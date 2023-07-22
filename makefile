all: myls mysearch mystat mytail

myls: myls-Ahmed.c
	gcc -o myls myls-Ahmed.c
	
mysearch: mysearch-Ahmed.c
	gcc -o mysearch mysearch-Ahmed.c
	
mystat: mystat-Ahmed.c
	gcc -o mystat mystat-Ahmed.c

mytail: mytail-Ahmed.c
	gcc -o mytail mytail-Ahmed.c

clean:
	rm *.o myls mystat mysearch mytail