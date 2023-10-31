libmylib.a : load.o search.o
	ar -rs $@ $^ 

load.o:  load.c mylib.h
	cc -c load.c

search.o:  search.c mylib.h
	cc -c search.c
