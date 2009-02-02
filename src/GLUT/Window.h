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

#ifndef _LULZJS_OPENGL_GLUT_WINDOW_H
#define _LULZJS_OPENGL_GLUT_WINDOW_H

#include "common.h"

extern JSBool exec (JSContext* cx);
extern JSBool Window_initialize (JSContext* cx);

extern JSBool Window_constructor (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
extern void   Window_finalize (JSContext* cx, JSObject* object);

static JSClass Window_class = {
    "Window", 0,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, Window_finalize
};

extern JSBool Window_setEvent (JSContext *cx, JSObject *obj, jsval id, jsval *vp);

static JSFunctionSpec Window_methods[] = {
    {NULL}
};

#endif
