.PHONY: clean

out: calc.c case_all
	gcc calc.c -o calc.o
	./calc.o < case_all > out

# Your code here.

case_add: casegen.c
	gcc casegen.c -o casegen.o
	./casegen.o add 100 | cat > case_add

case_sub: casegen.c
	gcc casegen.c -o casegen.o
	./casegen.o sub 100 | cat > case_sub

case_mul: casegen.c
	gcc casegen.c -o casegen.o
	./casegen.o mul 100 | cat > case_mul

case_div: casegen.c
	gcc casegen.c -o casegen.o
	./casegen.o div 100 | cat > case_div

case_all: case_add case_sub case_mul case_div
	# without exception 
	cat case_add case_sub case_mul case_div > case_all


clean:
	rm -f out calc casegen case_*
