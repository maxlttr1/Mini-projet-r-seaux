all: pc1 pc2 pc3
CC = gcc

pc1: src/utils.c src/pc1.c
	$(CC) -Wall -o $@.run $^


pc2: src/utils.c src/pc2.c
	$(CC) -Wall -o $@.run $^

pc3: src/utils.c src/pc3.c
	$(CC) -Wall -o $@.run $^

clean:
	rm -f *.run

