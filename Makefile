Test: Test.o
	gcc -o Test -g Test.o -lpthread -lm

Test.o: Test.c
	gcc -g -c -Wall -pthread Test.c

clean:
	rm -f *.gch *.o Test

