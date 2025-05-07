all: pc_test1 pc_test2
CC = gcc

pc_test1: src/utils.c src/pc_test1.c
	$(CC) -Wall -o $@.run $^


pc_test2: src/utils.c src/pc_test2.c
	$(CC) -Wall -o $@.run $^

clean:
	rm -f *.run

