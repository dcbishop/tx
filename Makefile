CXX = $(shell which cpp g++ colorgcc | tail -n 1)
OBJS = console.o Area.o Interface.o ResourceManager.o ImageManager.o Object.o Camera.o
all: tx

SDL_CONFIG=sdl-config
SDL_LIBS:= $(shell ${SDL_CONFIG} --libs)
SDL_CFLAGS:= $(shell ${SDL_CONFIG} --cflags)

LIBS = ${SDL_LIBS} -lmxml -lrcbc  -lGL -lGLU -lIL
CFLAGS = ${SDL_CFLAGS} $(shell pkg-config --cflags mxml)

tx: tx.cpp ${OBJS}
	${CXX} ${OBJS} $< -o tx ${LIBS} ${CFLAGS} -Wall

.cpp.o:
	${CXX} ${LIBS} ${CFLAGS} -c $< -Wall

clean:
	rm -f *.o tx tx.exe *.a *~ core
