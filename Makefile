CXX=g++
OBJS = console.o Area.o Interface.o ImageManager.o
all: tx
LIBS = /usr/local/lib/librcbc.a -lrcbc -L.

tx: tx.cpp ${OBJS}
	${CXX} ${OBJS} $< -static -o tx ${LIBS}

clean:
	rm -f *.o tx tx.exe *.a *~ core
