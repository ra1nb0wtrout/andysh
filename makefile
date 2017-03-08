CC=gcc

andysh: andysh.c builtins.h
	gcc andysh.c -o andysh

clean:
	rm andysh
