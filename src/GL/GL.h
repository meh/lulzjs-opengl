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

#ifndef _LULZJS_OPENGL_GL_H
#define _LULZJS_OPENGL_GL_H

#include "common.h"

extern "C" JSBool exec (JSContext* cx);
JSBool GL_initialize (JSContext* cx);

static JSClass GL_class = {
    "GL", 0,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_PropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, JS_FinalizeStub
};

JSBool GL_enable (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

JSBool GL_clear (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
JSBool GL_flush (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

JSBool GL_begin (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
JSBool GL_end (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

JSBool GL_loadIdentity (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

JSBool GL_color (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
JSBool GL_normal (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
JSBool GL_vertex (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

JSBool GL_rotate (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);
JSBool GL_translate (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval);

static JSFunctionSpec GL_methods[] = {
    {"enable", GL_enable, 0, 0, 0},

    {"clear", GL_clear, 0, 0, 0},
    {"flush", GL_flush, 0, 0, 0},

    {"loadIdentity", GL_loadIdentity, 0, 0, 0},

    {"begin", GL_begin, 0, 0, 0},
    {"end",   GL_end,   0, 0, 0},

    {"color",  GL_color,  0, 0, 0},
    {"normal", GL_normal, 0, 0, 0},
    {"vertex", GL_vertex, 0, 0, 0},

    {"rotate", GL_rotate, 0, 0, 0},
    {"translate", GL_translate, 0, 0, 0},
    {NULL}
};

#endif
