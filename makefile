treetest: treetest.c mylib/mylib.h
	cc -o treetest treetest.c -l mylib -L mylib
treeload: treeload.c mylib/mylib.h
	cc -o treeload treeload.c -l mylib -L mylib
treesearch: treesearch.c mylib/mylib.h
	cc -o treesearch treesearch.c -l mylib -L mylib