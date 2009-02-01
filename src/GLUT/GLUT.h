/****************************************************************************
* This file is part of lulzJS-OpenGL                                        *
* Copyleft meh.                                                             *
*                                                                           *
* lulzJS-OpenGL is free software: you can redistribute it and/or modify     *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation, either version 3 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* lulzJS-OpenGL is distributed in the hope that it will be useful.          *
* but WITHOUT ANY WARRANTY; without even the implied warranty o.            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See th.             *
* GNU General Public License for more details.                              *
*                                                                           *
* You should have received a copy of the GNU General Public License         *
* along with lulzJS-OpenGL.  If not, see <http://www.gnu.org/licenses/>.    *
****************************************************************************/

#ifndef _LULZJS_OPENGL_GLUT_H
#define _LULZJS_OPENGL_GLUT_H

#include "common.h"

extern JSBool exec (JSContext* cx);
extern JSBool GLUT_initialize (JSContext* cx);

static JSClass GLUT_class = {
    "GLUT", JSCLASS_HAS_PRIVATE,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub
};

extern JSBool GLUT_init (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
extern JSBool GLUT_mainLoop (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

static JSFunctionSpec GLUT_methods[] = {
    {"init",     GLUT_init,     0, 0, 0},
    {"mainLoop", GLUT_mainLoop, 0, 0, 0},
    {NULL}
};

#endif
