CXX = $(shell which cpp g++ colorgcc | tail -n 1)
OBJS = console.o Area.o Interface.o ResourceManager.o ImageManager.o Object.o Camera.o Creature.o DynamicFloat.o AccelerateFloat.o Physics.o Scripting.o RigidBody.o
all: tx

SDL_CONFIG=sdl-config
SDL_LIBS:= $(shell ${SDL_CONFIG} --libs)
SDL_CFLAGS:= $(shell ${SDL_CONFIG} --cflags)

LIBS = ${SDL_LIBS} -lrcbc  -lGL -lGLU -lIL -lluabind
CFLAGS = ${SDL_CFLAGS} $(shell pkg-config --cflags lua5.1) $(shell pkg-config --cflags mxml) $(shell pkg-config --cflags bullet --static)
INC = $(shell pkg-config --libs lua5.1) $(shell pkg-config --libs mxml) $(shell pkg-config --libs bullet --static) 

tx: tx.cpp ${OBJS}
	${CXX} ${OBJS} ${INC} $< -o tx ${LIBS} ${CFLAGS} -Wall

.cpp.o:
	${CXX} ${LIBS} ${CFLAGS} -c $< -Wall

clean:
	rm -f *.o tx tx.exe *.a *~ core *.gch moc_*.c
