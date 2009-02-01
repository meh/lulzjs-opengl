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

#include "Window.h"

JSBool exec (JSContext* cx) { return Window_initialize(cx); }

JSBool
Window_initialize (JSContext* cx)
{
    jsval jsParent;
    JS_GetProperty(cx, JS_GetGlobalObject(cx), "OpenGL", &jsParent);
    JS_GetProperty(cx, JSVAL_TO_OBJECT(jsParent), "GLUT", &jsParent);
    JSObject* parent = JSVAL_TO_OBJECT(jsParent);

    JSObject* object = JS_InitClass(
        cx, parent, NULL, &Window_class,
        Window_constructor, 1, NULL, Window_methods, NULL, NULL
    );

    if (object) {
        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool
Window_constructor (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* parent;
    JSObject* options;
    jsval x, y, width, height, title;
    jsint offset = 0;

    if (argc < 1) {
        JS_ReportError(cx, "Not enough parameters.");
        return JS_FALSE;
    }

    if (argc == 2) {
        JS_ValueToObject(cx, argv[0], &parent);

        if (!JS_OBJECT_IS(cx, OBJECT_TO_JSVAL(parent), "OpenGL.GLUT.Window")) {
            JS_ReportError(cx, "You have to pass a Window object.");
            return JS_FALSE;
        }

        offset = 1;
    }

    JS_ValueToObject(cx, argv[offset], &options);

    JS_GetProperty(cx, options, "title", &title);
    if (JSVAL_IS_VOID(title) || JSVAL_IS_UNDEFINED(title)) {
        JS_GetProperty(cx, options, "Title", &title);

        if (JSVAL_IS_VOID(title) || JSVAL_IS_UNDEFINED(title)) {
            title = STRING_TO_JSVAL(JS_NewString(cx, JS_strdup(cx, "lulzJS", strlen("lulzJS"))));
        }
    }
    
    JS_GetProperty(cx, options, "width", &width);
    if (JSVAL_IS_VOID(width) || JSVAL_IS_UNDEFINED(width)) {
        JS_GetProperty(cx, options, "Width", &width);
    }

    JS_GetProperty(cx, options, "height", &height);
    if (JSVAL_IS_VOID(height) || JSVAL_IS_UNDEFINED(height)) {
        JS_GetProperty(cx, options, "Height", &height);
    }

    JS_GetProperty(cx, options, "x", &x);
    if (JSVAL_IS_VOID(x) || JSVAL_IS_UNDEFINED(x)) {
        JS_GetProperty(cx, options, "X", &x);
    }

    JS_GetProperty(cx, options, "y", &y);
    if (JSVAL_IS_VOID(y) || JSVAL_IS_UNDEFINED(y)) {
        JS_GetProperty(cx, options, "Y", &y);
    }

    if (!JSVAL_IS_INT(width) || !JSVAL_IS_INT(height) || !JSVAL_IS_INT(x) || !JSVAL_IS_INT(y)) {
        JS_ReportError(cx, "A parameter is missing.");
        return JS_FALSE;
    }
    
    int* win = JS_malloc(cx, sizeof(int));
    switch (argc) {
        case 1: {
            win = glutCreateWindow();
(                JSVAL_TO_INT(border ? height+3 : height), JSVAL_TO_INT(border ? width+3 : width),
                JSVAL_TO_INT(y), JSVAL_TO_INT(x)
            );
        } break;

        case 2: {
            WINDOW* parentWin = JS_GetPrivate(cx, parent);
            win = subwin(parentWin,
                JSVAL_TO_INT(border ? height+3 : height), JSVAL_TO_INT(border ? width+3 : width),
                JSVAL_TO_INT(y), JSVAL_TO_INT(x)
            );
        } break;
    }
    JS_SetPrivate(cx, object, win);

    JSObject* Size   = JS_NewObject(cx, NULL, NULL, NULL);
    jsval     jsSize = OBJECT_TO_JSVAL(Size);
    JS_SetProperty(cx, object, "Size", &jsSize);
        JS_SetProperty(cx, Size, "Width", &width);
        JS_SetProperty(cx, Size, "Height", &height);

    JSObject* Position   = JS_NewObject(cx, NULL, NULL, NULL);
    jsval     jsPosition = OBJECT_TO_JSVAL(Position);
    JS_SetProperty(cx, object, "Position", &jsPosition);
        JS_SetProperty(cx, Position, "X", &x);
        JS_SetProperty(cx, Position, "Y", &y);

    return JS_TRUE;
}

