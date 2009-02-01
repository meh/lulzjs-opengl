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

void __Window_setWindow (JSContext* actualContext, int win, JSObject* Window);

JSContext* actualContext;
JSObject*  actualWindow;

void onDisplay (void); // onDisplay
void onOverlay (void); // onOverlay
void onResize (int width, int height); // onResize
void onKey (unsigned char key, int x, int y); // onKey
void onMouseClick (int button, int state, int x, int y); // Mouse.onDown Mouse.onUp Mouse.onClick
void onMouseDrag (int x, int y); // Mouse.onDrag

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
    JSObject* parent = NULL;
    JSObject* events = NULL;
    JSObject* options;
    jsval x, y, width, height, title;
    jsint offset = 0;

    jsval check = JS_EVAL(cx, "OpenGL.GLUT.inited");
    JSBool inited; JS_ValueToBoolean(cx, check, &inited);

    if (!inited) {
        JS_ReportError(cx, "You have to GLUT.init first.");
        return JS_FALSE;
    }

    if (argc < 1) {
        JS_ReportError(cx, "Not enough parameters.");
        return JS_FALSE;
    }

    if (argc >= 2) {
        JS_ValueToObject(cx, argv[0], &parent);

        if (!JS_OBJECT_IS(cx, OBJECT_TO_JSVAL(parent), "OpenGL.GLUT.Window")) {
            if (argc == 3) {
                JS_ReportError(cx, "You have to pass a Window object.");
                return JS_FALSE;
            }
            else {
                events = parent;
                parent = NULL;
            }
        }
        else {
            offset = 1;
        }
    }

    JS_ValueToObject(cx, argv[offset], &options);

    JS_GetProperty(cx, options, "title", &title);
    if (JSVAL_IS_VOID(title) || JSVAL_IS_VOID(title)) {
        JS_GetProperty(cx, options, "Title", &title);

        if (JSVAL_IS_VOID(title) || JSVAL_IS_VOID(title)) {
            title = STRING_TO_JSVAL(JS_NewString(cx, JS_strdup(cx, "lulzJS"), strlen("lulzJS")));
        }
    }
    
    JS_GetProperty(cx, options, "width", &width);
    if (JSVAL_IS_VOID(width) || JSVAL_IS_VOID(width)) {
        JS_GetProperty(cx, options, "Width", &width);
    }

    JS_GetProperty(cx, options, "height", &height);
    if (JSVAL_IS_VOID(height) || JSVAL_IS_VOID(height)) {
        JS_GetProperty(cx, options, "Height", &height);
    }

    JS_GetProperty(cx, options, "x", &x);
    if (JSVAL_IS_VOID(x) || JSVAL_IS_VOID(x)) {
        JS_GetProperty(cx, options, "X", &x);

        if (JSVAL_IS_VOID(x) || JSVAL_IS_VOID(x)) {
            x = INT_TO_JSVAL(0);
        }
    }

    JS_GetProperty(cx, options, "y", &y);
    if (JSVAL_IS_VOID(y) || JSVAL_IS_VOID(y)) {
        JS_GetProperty(cx, options, "Y", &y);

        if (JSVAL_IS_VOID(y) || JSVAL_IS_VOID(y)) {
            y = INT_TO_JSVAL(0);
        }
    }

    if (!JSVAL_IS_INT(width) || !JSVAL_IS_INT(height) || !JSVAL_IS_INT(x) || !JSVAL_IS_INT(y)) {
        JS_ReportError(cx, "A parameter is missing.");
        return JS_FALSE;
    }
    
    int* win = JS_malloc(cx, sizeof(int));
    if (parent) {
        int* parentWin = JS_GetPrivate(cx, parent);
        *win = glutCreateSubWindow(*parentWin,
            JSVAL_TO_INT(x), JSVAL_TO_INT(y),
            JSVAL_TO_INT(width), JSVAL_TO_INT(height)
        );
    }
    else {
        *win = glutCreateWindow(JS_GetStringBytes(JS_ValueToString(cx, title)));
        __Window_setWindow(cx, *win, object);
        glutPositionWindow(JSVAL_TO_INT(x), JSVAL_TO_INT(y));
        glutReshapeWindow(JSVAL_TO_INT(width), JSVAL_TO_INT(height));
    }
    JS_SetPrivate(cx, object, win);

    JSObject* Mouse = JS_NewObject(cx, NULL, NULL, NULL);
    jsval jsMouse   = OBJECT_TO_JSVAL(Mouse);
    JS_SetProperty(cx, object, "Mouse", &jsMouse);

    // TODO: Add the array of ints to get the window corresponding to the int

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

    JS_DefineProperty(cx, object, "onDisplay", JSVAL_VOID, NULL, Window_set_onDisplay, 0);

    glutDisplayFunc(&onDisplay);

    // Clean callbacks
    glutOverlayDisplayFunc(NULL);
    glutReshapeFunc(NULL);
    glutKeyboardFunc(NULL);
    glutMouseFunc(NULL);
    glutMotionFunc(NULL);
    glutPassiveMotionFunc(NULL);

    if (events) {
        jsval event;

        JS_GetProperty(cx, events, "onDisplay", &event);
        if (JSVAL_IS_OBJECT(event)) {
            if (!JS_ObjectIsFunction(cx, JSVAL_TO_OBJECT(event))) {
                event = JS_EVAL(cx, "Function.empty");
            }
        }
    }

    return JS_TRUE;
}

void
Window_finalize (JSContext* cx, JSObject* object)
{
    int* win = JS_GetPrivate(cx, object);

    if (win) {
        JS_free(cx, win);
    }
}


JSBool
Window_set_onDisplay (JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
    return JS_TRUE;
}

void
__Window_setWindow (JSContext* cx, int win, JSObject* Window)
{
    actualContext = cx;
    actualWindow  = Window;

    glutSetWindow(win);
}

// GLUT callbacks
void onDisplay (void)
{
    jsval jsFunc; JS_GetProperty(actualContext, actualWindow, "onDisplay", &jsFunc);
    jsval ret;
    JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 0, NULL, &ret);
}

void onOverlay (void)
{
    jsval jsFunc; JS_GetProperty(actualContext, actualWindow, "onOverlay", &jsFunc);

    jsval ret;
    JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 0, NULL, &ret);
}

void onResize (int width, int height)
{
    jsval jsFunc; JS_GetProperty(actualContext, actualWindow, "onResize", &jsFunc);

    jsval jsWidth  = INT_TO_JSVAL(width);
    jsval jsHeight = INT_TO_JSVAL(height);
    jsval jsSize; JS_GetProperty(actualContext, actualWindow, "Size", &jsSize);
    JSObject* Size = JSVAL_TO_OBJECT(jsSize);
        JS_SetProperty(actualContext, Size, "Width", &jsWidth);
        JS_SetProperty(actualContext, Size, "Height", &jsHeight);

    jsval ret;
    jsval argv[] = {INT_TO_JSVAL(width), INT_TO_JSVAL(height)};
    JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 2, argv, &ret);
}

void onKey (unsigned char key, int x, int y)
{
    jsval jsFunc; JS_GetProperty(actualContext, actualWindow, "onKey", &jsFunc);

    jsval ret;
    jsval argv[] = {INT_TO_JSVAL(key), INT_TO_JSVAL(x), INT_TO_JSVAL(y)};
    JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 3, argv, &ret);
}

void onMouseClick (int button, int state, int x, int y)
{
    jsval jsMouse; JS_GetProperty(actualContext, actualWindow, "Mouse", &jsMouse);
    JSObject* Mouse = JSVAL_TO_OBJECT(jsMouse);

    jsval jsFunc, ret;
    jsval argv[] = {INT_TO_JSVAL(button), INT_TO_JSVAL(x), INT_TO_JSVAL(y)};

    if (state == GLUT_DOWN) {
        JS_GetProperty(actualContext, Mouse, "onDown", &jsFunc);

        if (JSVAL_IS_OBJECT(jsFunc)) {
            if (JS_ObjectIsFunction(actualContext, JSVAL_TO_OBJECT(jsFunc))) {
                JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 3, argv, &ret);
            }
        }
    }
    else {
        JS_GetProperty(actualContext, Mouse, "onUp", &jsFunc);
        if (JSVAL_IS_OBJECT(jsFunc)) {
            if (JS_ObjectIsFunction(actualContext, JSVAL_TO_OBJECT(jsFunc))) {
                JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 3, argv, &ret);
            }
        }

        JS_GetProperty(actualContext, Mouse, "onClick", &jsFunc);
        if (JSVAL_IS_OBJECT(jsFunc)) {
            if (JS_ObjectIsFunction(actualContext, JSVAL_TO_OBJECT(jsFunc))) {
                JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 3, argv, &ret);
            }
        }
    }
}

void onMouseDrag (int x, int y)
{
    jsval jsFunc; JS_GetProperty(actualContext, actualWindow, "onDrag", &jsFunc);

    jsval ret;
    jsval argv[] = {INT_TO_JSVAL(x), INT_TO_JSVAL(y)};
    JS_CallFunctionValue(actualContext, actualWindow, jsFunc, 2, argv, &ret);
}

