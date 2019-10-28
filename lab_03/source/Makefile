app.exe: menu.o smatrix.o err.o main.o linked_list.o test.o matrix.o 
	gcc -std=c99 -Wall -Werror -o $@ $^
menu.o: menu.c 
	gcc -std=c99 -Wall -Werror -c $^
smatrix.o: smatrix.c 
	gcc -std=c99 -Wall -Werror -c $^
err.o: err.c 
	gcc -std=c99 -Wall -Werror -c $^
main.o: main.c 
	gcc -std=c99 -Wall -Werror -c $^
linked_list.o: linked_list.c 
	gcc -std=c99 -Wall -Werror -c $^
test.o: test.c 
	gcc -std=c99 -Wall -Werror -c $^
matrix.o: matrix.c 
	gcc -std=c99 -Wall -Werror -c $^
clean:
	rm *.o *.exe