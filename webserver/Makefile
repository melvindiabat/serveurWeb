# Ces variables servent à préciser le compilateur que l’on veut utiliser
# ainsi que les paramètres de compilation
CC=gcc
LD=gcc
CFLAGS=-Wall -W -Werror
LDFLAGS =


EXE = pawnee

HEADERS=$(wildcard *.h)
CFILES=$(wildcard *.c)

OBJS = $(CFILES:.c =.o)

.PHONY: all clean mrproper

all: $(EXE)

$(EXE): $(OBJS)
		$(LD) $^ $(LDFLAGS) -o $@

makefile.dep: $(CFILES) $(HEADERS)
		$(CC) -MM $(CFILES) > $@

clean :
		$(RM) $(OBJS) makefile.dep

mrproper: clean
			$(RM) $(EXE)
clear:
	rm -f *.o
real-clear:
	rm -f $(EXE)

include makefile.dep
