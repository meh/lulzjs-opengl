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

#include "GLUT.h"

void onDisplay (void)
{

}

JSBool exec (JSContext* cx) { return GLUT_initialize(cx); }

JSBool
GLUT_initialize (JSContext* cx)
{
    jsval jsParent;
    JS_GetProperty(cx, JS_GetGlobalObject(cx), "OpenGL", &jsParent);
    JSObject* parent = JSVAL_TO_OBJECT(jsParent);

    JSObject* object = JS_DefineObject(
        cx, parent,
        GLUT_class.name, &GLUT_class, NULL, 
        JSPROP_PERMANENT|JSPROP_READONLY|JSPROP_ENUMERATE
    );

    if (object) {
        JS_DefineFunctions(cx, object, GLUT_methods);

        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool
GLUT_init (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* arguments;

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &arguments)) {
        JS_ReportError(cx, "Not enough parameters.");
        return JS_FALSE;
    }

    if (!JS_IsArrayObject(cx, arguments)) {
        JS_ReportError(cx, "You have to pass an array.");
        return JS_FALSE;
    }

    jsuint length; JS_GetArrayLength(cx, arguments, &length);
    char** array = JS_malloc(cx, length*sizeof(char*));

    jsuint i;
    for (i = 0; i < length; i++) {
        jsval val; JS_GetElement(cx, arguments, i, &val);
        array[i] = JS_strdup(cx, JS_GetStringBytes(JS_ValueToString(cx, val)));
    }

    glutInit((int*)&length, array);

    jsval inited = JSVAL_TRUE;
    JS_SetProperty(cx, object, "inited", &inited);

    return JS_TRUE;
}

JSBool
GLUT_mainLoop (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    glutMainLoop();
    return JS_TRUE;
}


