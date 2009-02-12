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

        jsval property;

        JSObject* DisplayModes = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(DisplayModes);
        JS_SetProperty(cx, object, "DisplayModes", &property);
           property = INT_TO_JSVAL(GLUT_RGB);
           JS_SetProperty(cx, DisplayModes, "RGB", &property);
           property = INT_TO_JSVAL(GLUT_RGBA);
           JS_SetProperty(cx, DisplayModes, "RGBA", &property);
           property = INT_TO_JSVAL(GLUT_INDEX);
           JS_SetProperty(cx, DisplayModes, "Index", &property);
           property = INT_TO_JSVAL(GLUT_SINGLE);
           JS_SetProperty(cx, DisplayModes, "Single", &property);
           property = INT_TO_JSVAL(GLUT_DOUBLE);
           JS_SetProperty(cx, DisplayModes, "Double", &property);
           property = INT_TO_JSVAL(GLUT_ACCUM);
           JS_SetProperty(cx, DisplayModes, "Accum", &property);
           property = INT_TO_JSVAL(GLUT_ALPHA);
           JS_SetProperty(cx, DisplayModes, "Alpha", &property);
           property = INT_TO_JSVAL(GLUT_DEPTH);
           JS_SetProperty(cx, DisplayModes, "Depth", &property);
           property = INT_TO_JSVAL(GLUT_STENCIL);
           JS_SetProperty(cx, DisplayModes, "Stencil", &property);
           property = INT_TO_JSVAL(GLUT_MULTISAMPLE);
           JS_SetProperty(cx, DisplayModes, "MultiSample", &property);
           property = INT_TO_JSVAL(GLUT_STEREO);
           JS_SetProperty(cx, DisplayModes, "Stereo", &property);
           property = INT_TO_JSVAL(GLUT_LUMINANCE);
           JS_SetProperty(cx, DisplayModes, "Luminance", &property);

        JSObject* Keys = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Keys);
        JS_SetProperty(cx, object, "Keys", &property);
            property = OBJECT_TO_JSVAL(JS_GetFunctionObject(
                JS_NewFunction(cx, GLUT_KeyF, 1, 0, NULL, "KEY_F")
            ));
            JS_SetProperty(cx, Keys, "F", &property);
            property = INT_TO_JSVAL(GLUT_KEY_LEFT);
            JS_SetProperty(cx, Keys, "Left", &property);
            property = INT_TO_JSVAL(GLUT_KEY_UP);
            JS_SetProperty(cx, Keys, "Up", &property);
            property = INT_TO_JSVAL(GLUT_KEY_RIGHT);
            JS_SetProperty(cx, Keys, "Right", &property);
            property = INT_TO_JSVAL(GLUT_KEY_DOWN);
            JS_SetProperty(cx, Keys, "Down", &property);
            property = INT_TO_JSVAL(GLUT_KEY_PAGE_UP);
            JS_SetProperty(cx, Keys, "PageUp", &property);
            property = INT_TO_JSVAL(GLUT_KEY_PAGE_DOWN);
            JS_SetProperty(cx, Keys, "PageDown", &property);
            property = INT_TO_JSVAL(GLUT_KEY_HOME);
            JS_SetProperty(cx, Keys, "Home", &property);
            property = INT_TO_JSVAL(GLUT_KEY_END);
            JS_SetProperty(cx, Keys, "End", &property);
            property = INT_TO_JSVAL(GLUT_KEY_INSERT);
            JS_SetProperty(cx, Keys, "Insert", &property);
            property = INT_TO_JSVAL(24);
            JS_SetProperty(cx, Keys, "Cancel", &property);
            property = INT_TO_JSVAL(27);
            JS_SetProperty(cx, Keys, "Escape", &property);
            property = INT_TO_JSVAL(32);
            JS_SetProperty(cx, Keys, "Space", &property);
            property = INT_TO_JSVAL(127);
            JS_SetProperty(cx, Keys, "Delete", &property);

        JSObject* Mouse = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Mouse);
        JS_SetProperty(cx, object, "Mouse", &property);
            property = INT_TO_JSVAL(GLUT_LEFT_BUTTON);
            JS_SetProperty(cx, Mouse, "Left", &property);
            property = INT_TO_JSVAL(GLUT_MIDDLE_BUTTON);
            JS_SetProperty(cx, Mouse, "Middle", &property);
            property = INT_TO_JSVAL(GLUT_RIGHT_BUTTON);
            JS_SetProperty(cx, Mouse, "Right", &property);

        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool
GLUT_KeyF (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    if (argc < 1) {
        JS_ReportError(cx, "Not enough parameters.");
        return JS_FALSE;
    }

    jsint n; JS_ValueToInt32(cx, argv[0], &n);

    if (n < 1 || n > 12) {
        JS_ReportError(cx, "Out of range.");
        return JS_FALSE;
    }

    switch (n) {
        case  1: *rval = INT_TO_JSVAL(GLUT_KEY_F1); break;
        case  2: *rval = INT_TO_JSVAL(GLUT_KEY_F2); break;
        case  3: *rval = INT_TO_JSVAL(GLUT_KEY_F3); break;
        case  4: *rval = INT_TO_JSVAL(GLUT_KEY_F4); break;
        case  5: *rval = INT_TO_JSVAL(GLUT_KEY_F5); break;
        case  6: *rval = INT_TO_JSVAL(GLUT_KEY_F6); break;
        case  7: *rval = INT_TO_JSVAL(GLUT_KEY_F7); break;
        case  8: *rval = INT_TO_JSVAL(GLUT_KEY_F8); break;
        case  9: *rval = INT_TO_JSVAL(GLUT_KEY_F9); break;
        case 10: *rval = INT_TO_JSVAL(GLUT_KEY_F10); break;
        case 11: *rval = INT_TO_JSVAL(GLUT_KEY_F11); break;
        case 12: *rval = INT_TO_JSVAL(GLUT_KEY_F12); break;
    }

    return JS_TRUE;
}


JSBool
GLUT_init (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* arguments;
    int32     bits = 0;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 2 || !JS_ConvertArguments(cx, argc, argv, "oi", &arguments, &bits)) {
        JS_ReportError(cx, "Not enough parameters.");
        return JS_FALSE;
    }

    if (!JS_IsArrayObject(cx, arguments)) {
        JS_ReportError(cx, "You have to pass an array.");
        return JS_FALSE;
    }

    jsuint length; JS_GetArrayLength(cx, arguments, &length);
    char** array = new char*[length];

    jsuint i;
    for (i = 0; i < length; i++) {
        jsval val; JS_GetElement(cx, arguments, i, &val);
        array[i] = strdup(JS_GetStringBytes(JS_ValueToString(cx, val)));
    }

    glutInit((int*)&length, array);
    for (i = 0; i < length; i++) {
        free(array[i]);
    }
    delete array;
    glutInitDisplayMode(bits);

    jsval inited = JSVAL_TRUE;
    JS_SetProperty(cx, object, "inited", &inited);

    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);

    return JS_TRUE;
}

JSBool
GLUT_mainLoop (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    glutMainLoop();
    return JS_TRUE;
}

JSBool
GLUT_swapBuffers (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    glutSwapBuffers();
    return JS_TRUE;
}

