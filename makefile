MAKEFLAGS=-j $(if $(CORES),$(CORES),1)
CC=gcc
CFLAGS=-Wall -DNDEBUG -O3
LIBS=-lm
all: yalsat palsat libyals.a
yalsat: main.o libyals.a makefile
	$(CC) $(CFLAGS) -o $@ main.o -L. -lyals $(LIBS)
palsat: pain.o libyals.a makefile
	$(CC) $(CFLAGS) -o $@ pain.o -L. -lyals $(LIBS) -pthread
libyals.a: yals.o config.o
	ar rc $@ yals.o config.o
	ranlib $@
main.o: main.c yals.h yils.h makefile
	$(CC) $(CFLAGS) -c main.c
pain.o: main.c yals.h yils.h makefile
	$(CC) $(CFLAGS) -DPALSAT -o $@ -pthread -c main.c
yals.o: yals.c yals.h yils.h makefile
	$(CC) $(CFLAGS) -c yals.c
config.o: config.c config.h cflags.h yils.h makefile
	$(CC) $(CFLAGS) $(CFLAGS) -c config.c
config.h: VERSION yals.c yals.h yils.h main.c
	rm -f $@; ./mkconfig.sh >$@
cflags.h: makefile
	rm -f $@
	echo '#define YALS_CC "$(shell $(CC) --version|head -1)"' >>$@
	echo '#define YALS_CFLAGS "$(CFLAGS)"' >>$@
clean:
	rm -f yalsat *.a *.o makefile config.h cflags.h
