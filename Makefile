VERSION = 0.1

CC         = gcc
CXX        = g++
BINDIR     = /usr/bin
LJS_LIBDIR = /usr/lib/lulzjs
CFLAGS     = -Os -DXP_UNIX -DJS_THREADSAFE -D__LIB_VERSION__="\"${VERSION}\"" $(shell js-config --cflags) -I./src
LDFLAGS    = $(shell js-config --libs | sed 's/-dynamic.*/-lm/') -llulzjs

ifdef DEBUG
CFLAGS += -g -Wall
endif

ifdef DDEBUG
CFLAGS += -DDEBUG -g -Wall
endif

LIB_DIR     = src
LIB         = ${LIB_DIR}/OpenGL.o ${LIB_DIR}/GL/GL.o ${LIB_DIR}/GLU/GLU.o ${LIB_DIR}/GLUT/GLUT.o ${LIB_DIR}/GLUT/Window.o
LIB_CFLAGS  = ${CFLAGS}
LIB_LDFLAGS = ${LDFLAGS} -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

all: lib

lib: $(LIB)

$(LIB) : $(LIB:.o=.cpp)
	${CXX} ${LIB_CFLAGS} -fPIC -c $*.cpp -o $*.lo
	${CXX} ${LIB_LDFLAGS} -dynamiclib -shared -Wl,-soname,`basename $*`.so -o $*.o $*.lo -lc

lib_install: lib
	mkdir -p ${LJS_LIBDIR}/OpenGL
	mkdir -p ${LJS_LIBDIR}/OpenGL/GL
	mkdir -p ${LJS_LIBDIR}/OpenGL/GLU
	mkdir -p ${LJS_LIBDIR}/OpenGL/GLUT
########
	cp -f  ${LIB_DIR}/init.js			${LJS_LIBDIR}/OpenGL/init.js
	cp -f  ${LIB_DIR}/OpenGL.o			${LJS_LIBDIR}/OpenGL/OpenGL.so
	cp -f  ${LIB_DIR}/OpenGL.js			${LJS_LIBDIR}/OpenGL/OpenGL.js
########
	cp -f  ${LIB_DIR}/GL/init.js		${LJS_LIBDIR}/OpenGL/GL/init.js
	cp -f  ${LIB_DIR}/GL/GL.o			${LJS_LIBDIR}/OpenGL/GL/GL.so
	cp -f  ${LIB_DIR}/GL/GL.js			${LJS_LIBDIR}/OpenGL/GL/GL.js
########
	cp -f  ${LIB_DIR}/GLU/init.js		${LJS_LIBDIR}/OpenGL/GLU/init.js
	cp -f  ${LIB_DIR}/GLU/GLU.o			${LJS_LIBDIR}/OpenGL/GLU/GLU.so
	cp -f  ${LIB_DIR}/GLU/GLU.js		${LJS_LIBDIR}/OpenGL/GLU/GLU.js
########
	cp -f  ${LIB_DIR}/GLUT/init.js		${LJS_LIBDIR}/OpenGL/GLUT/init.js
	cp -f  ${LIB_DIR}/GLUT/GLUT.o		${LJS_LIBDIR}/OpenGL/GLUT/GLUT.so
	cp -f  ${LIB_DIR}/GLUT/GLUT.js		${LJS_LIBDIR}/OpenGL/GLUT/GLUT.js
	cp -f  ${LIB_DIR}/GLUT/Window.o		${LJS_LIBDIR}/OpenGL/GLUT/Window.so
	cp -f  ${LIB_DIR}/GLUT/Window.js	${LJS_LIBDIR}/OpenGL/GLUT/Window.js
#######
	chmod -R a+rx ${LJS_LIBDIR}/OpenGL

lib_uninstall:
	rm -rf ${LJS_LIBDIR}/OpenGL


install: lib_install
uninstall: lib_uninstall

clean:
	find src|egrep "\.l?o"|xargs rm -f
