# Makefile
# Compilation des primitives UDP
#

#CFLAGS	+= -Wall -Wmissing-prototypes -Werror

CC = gcc

SOURCES_ALL	= \
	creePriseReception.c\
	creePriseEmission.c\
	recoit.c\
	envoie.c\
	\
	PC1-emetteur.c\
	\
	PC2-recepteur.c\
	\
	primitives.h\
	\
	Makefile\
	\
	README.txt

ARCHIVE_NAME = Exemple-PC1-emetteur-PC2-recepteur.tgz

all: PC1-emetteur PC2-recepteur primitives.a $(ARCHIVE_NAME) clean 

clean:
	rm -f *.a *.o core

$(ARCHIVE_NAME): $(SOURCES_ALL)
	tar zcf $@ $(SOURCES_ALL)

PC1-emetteur: PC1-emetteur.o primitives.a
	$(CC) -o $@ $^

PC2-recepteur: PC2-recepteur.o primitives.a
	$(CC) -o $@ $^

primitives.a: envoie.o recoit.o creePriseEmission.o creePriseReception.o
	ar rv $@ $^
	ranlib $@

