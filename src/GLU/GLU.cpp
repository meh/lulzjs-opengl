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

#include "GLU.h"

JSBool exec (JSContext* cx) { return GLU_initialize(cx); }

JSBool
GLU_initialize (JSContext* cx)
{
    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    jsval jsParent;
    JS_GetProperty(cx, JS_GetGlobalObject(cx), "OpenGL", &jsParent);
    JSObject* parent = JSVAL_TO_OBJECT(jsParent);

    JSObject* object = JS_DefineObject(
        cx, parent,
        GLU_class.name, &GLU_class, NULL, 
        JSPROP_PERMANENT|JSPROP_READONLY|JSPROP_ENUMERATE
    );

    if (object) {
        JS_DefineFunctions(cx, object, GLU_methods);

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool
GLU_lookAt (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* arrays;
    JSObject* eye;
    JSObject* center;
    JSObject* up;
    jsdouble eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &arrays)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval property;

    JS_GetProperty(cx, arrays, "eye", &property);
    if (!JSVAL_IS_OBJECT(property)) {
        JS_GetProperty(cx, arrays, "Eye", &property);

        if (JSVAL_IS_OBJECT(property)) {
            JS_ValueToObject(cx, property, &eye);
        }
        else {
            jsval eles[] = {INT_TO_JSVAL(0), INT_TO_JSVAL(0), INT_TO_JSVAL(0)};
            eye          = JS_NewArrayObject(cx, 3, eles);
        }
    }
    else {
        JS_ValueToObject(cx, property, &eye);
    }

    JS_GetProperty(cx, arrays, "center", &property);
    if (!JSVAL_IS_OBJECT(property)) {
        JS_GetProperty(cx, arrays, "Center", &property);

        if (JSVAL_IS_OBJECT(property)) {
            JS_ValueToObject(cx, property, &center);
        }
        else {
            jsval eles[] = {INT_TO_JSVAL(0), INT_TO_JSVAL(0), INT_TO_JSVAL(0)};
            center       = JS_NewArrayObject(cx, 3, eles);
        }
    }
    else {
        JS_ValueToObject(cx, property, &center);
    }

    JS_GetProperty(cx, arrays, "center", &property);
    if (!JSVAL_IS_OBJECT(property)) {
        JS_GetProperty(cx, arrays, "Center", &property);

        if (JSVAL_IS_OBJECT(property)) {
            JS_ValueToObject(cx, property, &up);
        }
        else {
            jsval eles[] = {INT_TO_JSVAL(0), INT_TO_JSVAL(0), INT_TO_JSVAL(0)};
            up           = JS_NewArrayObject(cx, 3, eles);
        }
    }
    else {
        JS_ValueToObject(cx, property, &up);
    }

    jsuint eyeLength, centerLength, upLength;
    JS_GetArrayLength(cx, eye, &eyeLength);
    JS_GetArrayLength(cx, center, &centerLength);
    JS_GetArrayLength(cx, up, &upLength);

    if (eyeLength != 3 || centerLength != 3 || upLength != 3) {
        JS_ReportError(cx, "Wrong number of values.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval element;

    JS_GetElement(cx, eye, 0, &element); JS_ValueToNumber(cx, element, &eyeX);
    JS_GetElement(cx, eye, 1, &element); JS_ValueToNumber(cx, element, &eyeY);
    JS_GetElement(cx, eye, 2, &element); JS_ValueToNumber(cx, element, &eyeZ);

    JS_GetElement(cx, center, 0, &element); JS_ValueToNumber(cx, element, &centerX);
    JS_GetElement(cx, center, 1, &element); JS_ValueToNumber(cx, element, &centerY);
    JS_GetElement(cx, center, 2, &element); JS_ValueToNumber(cx, element, &centerZ);

    JS_GetElement(cx, up, 0, &element); JS_ValueToNumber(cx, element, &upX);
    JS_GetElement(cx, up, 1, &element); JS_ValueToNumber(cx, element, &upY);
    JS_GetElement(cx, up, 2, &element); JS_ValueToNumber(cx, element, &upZ);

    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);
    return JS_TRUE;
}

