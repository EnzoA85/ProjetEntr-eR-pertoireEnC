treetest: treetest.c mylib/mylib.h
	cc -o treetest treetest.c -l mylib -L mylib