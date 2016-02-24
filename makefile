all: find test0 test1 test2

find:
	cl find.c search.c

test0:
	cl find.c search.c
	find line -i test.txt -o test0_output.txt
	
test1:
	cl find.c search.c
	find line -i test.txt -o test1_output.txt -c
	
test2:	
	cl find.c search.c
	find -c line -o test2_output.txt -i test.txt
	
test3:
	cl find.c search.c
	find mother -i book.txt
	
test4:
	cl find.c search.c
	find -i book.txt -c brother
	
test5: 
	cl find.c search.c
	find -i book.txt
	
test6: 
	cl find.c search.c
	find time -i 
	
test7: 
	cl find.c search.c
	find time -i test.txt -o

test8: 
	cl find.c search.c
	find time -i invalid.txt
	
test9:
	cl find.c search.c
	dir | find make
	
test10:
	cl find.c search.c
	dir | find make -o test10_output.txt
	
test11:
	cl find.c search.c
	dir | find time -i book.txt
	
clean:
	del *.obj
	del *.exe
	del *.asm