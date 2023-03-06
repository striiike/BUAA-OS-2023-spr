all: test.c
	gcc test.c -o test

run: test.c
	gcc test.c -o test
	./test

.PHONY: clean
clean:
	rm test
