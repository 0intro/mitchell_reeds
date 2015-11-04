LIB=libmitchellreeds.a

OFILES=\
	mitchell_reeds.o\

HFILES=\
	mitchell_reeds.h\

all: $(LIB) mitchell_reeds_test

$(OFILES): $(HFILES)

CC=gcc
LD=gcc
AR=ar
RANLIB=ranlib
CFLAGS=-Wall -Wextra -c -I. -g
LDFLAGS=

$(LIB): $(OFILES) $(HFILES)
	$(AR) r $(LIB) $(OFILES)
	$(RANLIB) $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) $*.c

mitchell_reeds_test: $(LIB)
	$(LD) $(LDFLAGS) -o mitchell_reeds_test mitchell_reeds_test.c $(LIB)

clean:
	rm -f *.o

nuke: clean
	rm -f *.a mitchell_reeds_test

install: $(LIB)
	cp $(LIB) /usr/local/lib
	cp mitchell_reeds.h /usr/local/include
