VERSION = 0.1

CC         = gcc
CXX        = g++
BINDIR     = /usr/bin
LJS_LIBDIR = /usr/lib/lulzjs
CFLAGS     = -Os -DXP_UNIX -DJS_THREADSAFE -D__LIB_VERSION__="\"${VERSION}\"" -I/usr/include/js -I./src
LDFLAGS    = -ljs -llulzjs

ifdef DEBUG
CFLAGS += -g
endif

ifdef DDEBUG
CFLAGS += -DDEBUG -g
endif

LIB_DIR     = src
LIB         = ${LIB_DIR}/OpenGL.o ${LIB_DIR}/GL/GL.o ${LIB_DIR}/GLUT/GLUT.o
LIB_CFLAGS  = ${CFLAGS}
LIB_LDFLAGS = ${LDFLAGS} -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

all: lib

lib: $(LIB)

$(LIB) : $(LIB:.o=.c)
	${CC} ${LIB_CFLAGS} -fPIC -c $*.c -o $*.lo
	${CC} ${LIB_LDFLAGS} -shared -Wl,-soname,`basename $*`.so -o $*.o $*.lo -lc

lib_install: lib
	mkdir -p ${LJS_LIBDIR}/OpenGL
########
	cp -f  ${LIB_DIR}/init.js		${LJS_LIBDIR}/OpenGL/init.js
########
	cp -f  ${LIB_DIR}/OpenGL.o		${LJS_LIBDIR}/OpenGL/OpenGL.so
	cp -f  ${LIB_DIR}/OpenGL.js		${LJS_LIBDIR}/OpenGL/OpenGL.js
########
	cp -f  ${LIB_DIR}/GL/GL.o		${LJS_LIBDIR}/OpenGL/GL/GL.so
	cp -f  ${LIB_DIR}/GL/GL.js		${LJS_LIBDIR}/OpenGL/GL/GL.js
########
	cp -f  ${LIB_DIR}/GLUT/GLUT.o	${LJS_LIBDIR}/OpenGL/GLUT/GLUT.so
	cp -f  ${LIB_DIR}/GLUT/GLUT.js	${LJS_LIBDIR}/OpenGL/GLUT/GLUT.js
#######
	chmod -R a+rx ${LJS_LIBDIR}/OpenGL

lib_uninstall:
	rm -rf ${LJS_LIBDIR}/OpenGL


install: lib_install
uninstall: lib_uninstall

clean:
	find src|egrep "\.l?o"|xargs rm -f
