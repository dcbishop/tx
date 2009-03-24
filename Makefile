CXX=g++
OBJS = console.o Area.o Interface.o ImageManager.o
all: tx
LIBS = /usr/local/lib/librcbc.a -lrcbc -L. ${shell sdl-config --libs}
CFLAGS = ${shell sdl-config --cflags}

tx: tx.cpp ${OBJS}
	${CXX} ${OBJS} $< -o tx ${LIBS}

.cpp.o:
	${CXX} ${LIBS} ${CFLAGS} -c $<

clean:
	rm -f *.o tx tx.exe *.a *~ core
