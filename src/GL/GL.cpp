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

#include "GL.h"

JSBool exec (JSContext* cx) { return GL_initialize(cx); }

JSBool
GL_initialize (JSContext* cx)
{
    jsval jsParent;
    JS_GetProperty(cx, JS_GetGlobalObject(cx), "OpenGL", &jsParent);
    JSObject* parent = JSVAL_TO_OBJECT(jsParent);

    JSObject* object = JS_DefineObject(
        cx, parent,
        GL_class.name, &GL_class, NULL, 
        JSPROP_PERMANENT|JSPROP_READONLY|JSPROP_ENUMERATE
    );

    if (object) {
        JS_DefineFunctions(cx, object, GL_methods);

        jsval property;

        JSObject* Capabilities = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Capabilities);
        JS_SetProperty(cx, object, "Capabilities", &property);
            property = INT_TO_JSVAL(GL_DEPTH_TEST);
            JS_SetProperty(cx, Capabilities, "DepthTest", &property);

        JSObject* Primitives = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Primitives);
        JS_SetProperty(cx, object, "Primitives", &property);
            property = INT_TO_JSVAL(GL_POINTS);
            JS_SetProperty(cx, Primitives, "Point", &property);
            property = INT_TO_JSVAL(GL_LINES);
            JS_SetProperty(cx, Primitives, "Line", &property);
            property = INT_TO_JSVAL(GL_LINE_LOOP);
            JS_SetProperty(cx, Primitives, "LineLoop", &property);
            property = INT_TO_JSVAL(GL_LINE_STRIP);
            JS_SetProperty(cx, Primitives, "LineStrip", &property);
            property = INT_TO_JSVAL(GL_TRIANGLES);
            JS_SetProperty(cx, Primitives, "Triangle", &property);
            property = INT_TO_JSVAL(GL_QUADS);
            JS_SetProperty(cx, Primitives, "Quad", &property);
            property = INT_TO_JSVAL(GL_QUAD_STRIP);
            JS_SetProperty(cx, Primitives, "QuadStrip", &property);
            property = INT_TO_JSVAL(GL_POLYGON);
            JS_SetProperty(cx, Primitives, "Polygon", &property);

        JSObject* VertexArrays = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(VertexArrays);
        JS_SetProperty(cx, object, "VertexArrays", &property);

        JSObject* MatrixMode = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(MatrixMode);
        JS_SetProperty(cx, object, "MatrixMode", &property);
            property = INT_TO_JSVAL(GL_MODELVIEW);
            JS_SetProperty(cx, MatrixMode, "ModelView", &property);
            property = INT_TO_JSVAL(GL_PROJECTION);
            JS_SetProperty(cx, MatrixMode, "Projection", &property);
            property = INT_TO_JSVAL(GL_TEXTURE);
            JS_SetProperty(cx, MatrixMode, "Texture", &property);

        JSObject* Points = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Points);
        JS_SetProperty(cx, object, "Points", &property);

        JSObject* Lines = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Lines);
        JS_SetProperty(cx, object, "Lines", &property);

        JSObject* Polygons = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Polygons);
        JS_SetProperty(cx, object, "Polygons", &property);
            property = INT_TO_JSVAL(GL_POINT);
            JS_SetProperty(cx, Polygons, "Point", &property);
            property = INT_TO_JSVAL(GL_LINE);

        JSObject* Buffers = JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Buffers);
        JS_SetProperty(cx, object, "Buffers", &property);
            property = INT_TO_JSVAL(GL_COLOR_BUFFER_BIT);
            JS_SetProperty(cx, Buffers, "Color", &property);
            property = INT_TO_JSVAL(GL_DEPTH_BUFFER_BIT);
            JS_SetProperty(cx, Buffers, "Depth", &property);
            property = INT_TO_JSVAL(GL_ACCUM_BUFFER_BIT);
            JS_SetProperty(cx, Buffers, "Accum", &property);

        return JS_TRUE;
    }

    return JS_FALSE;
}

JSBool
GL_enable (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    jsint bits;

    JS_BeginRequest(cx);
    if (argc != 1 || !JS_ConvertArguments(cx, argc, argv, "i", &bits)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_EndRequest(cx);
        return JS_FALSE;
    }
    JS_EndRequest(cx);

    glEnable(bits);

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_ENUM:      errorText = "The value isn't accepted."; break;
            case GL_INVALID_OPERATION: errorText = "You can't call GL.enable between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }
   
    return JS_TRUE;
}

JSBool
GL_disable (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    jsint bits;

    JS_BeginRequest(cx);
    if (argc != 1 || !JS_ConvertArguments(cx, argc, argv, "i", &bits)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_EndRequest(cx);
        return JS_FALSE;
    }
    JS_EndRequest(cx);

    glDisable(bits);

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_ENUM:      errorText = "The value isn't accepted."; break;
            case GL_INVALID_OPERATION: errorText = "You can't call GL.disable between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }
   
    return JS_TRUE;
}


JSBool
GL_clear (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    jsint bits;

    JS_BeginRequest(cx);
    if (argc != 1 || !JS_ConvertArguments(cx, argc, argv, "i", &bits)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_EndRequest(cx);
        return JS_FALSE;
    }
    JS_EndRequest(cx);

    glClear(bits);

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_VALUE:     errorText = "The value isn't accepted."; break;
            case GL_INVALID_OPERATION: errorText = "You can't call GL.clear between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }

    return JS_TRUE;
}

JSBool
GL_begin (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    jsint bits;

    JS_BeginRequest(cx);
    if (argc != 1 || !JS_ConvertArguments(cx, argc, argv, "i", &bits)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_EndRequest(cx);
        return JS_FALSE;
    }
    JS_EndRequest(cx);

    glBegin(bits);

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_ENUM:      errorText = "It's not an accepted value."; break;
            case GL_INVALID_OPERATION: errorText = "There's already a begin in execution."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }

    return JS_TRUE;
}

JSBool
GL_end (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    glEnd();

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_OPERATION: errorText = "There's no begin executed."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }

    return JS_TRUE;
}

JSBool
GL_loadIdentity (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    glLoadIdentity();

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_OPERATION: errorText = "You can't call GL.loadIdentity between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }

    return JS_TRUE;
}


JSBool
GL_flush (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    glFlush();

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_OPERATION: errorText = "You can't call GL.flush between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }

    return JS_TRUE;
}

JSBool
GL_normal (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* array;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &array)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsuint length;
    JS_GetArrayLength(cx, array, &length);

    if (length != 3) {
        JS_ReportError(cx, "Wrong number of values.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval jsX, jsY, jsZ;
    JS_GetElement(cx, array, 0, &jsX);
    JS_GetElement(cx, array, 1, &jsY);
    JS_GetElement(cx, array, 2, &jsZ);

    if (JSVAL_IS_DOUBLE(jsX) || JSVAL_IS_DOUBLE(jsY) || JSVAL_IS_DOUBLE(jsZ)) {
        jsdouble x, y, z;
        JS_ValueToNumber(cx, jsX, &x);
        JS_ValueToNumber(cx, jsY, &y);
        JS_ValueToNumber(cx, jsZ, &z);

        glNormal3d(x, y, z);
    }
    else {
        int32 x, y, z;
        JS_ValueToInt32(cx, jsX, &x);
        JS_ValueToInt32(cx, jsY, &y);
        JS_ValueToInt32(cx, jsZ, &z);

        glNormal3i(x, y, z);
    }

    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);
    return JS_TRUE;
}

JSBool
GL_vertex (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* array;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &array)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsuint length;
    JS_GetArrayLength(cx, array, &length);

    if (length < 2 || length > 4) {
        JS_ReportError(cx, "Wrong number of values.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval jsX, jsY, jsZ = JSVAL_VOID, jsW = JSVAL_VOID;

    switch (length) {
        case 4:
        JS_GetElement(cx, array, 3, &jsW);

        case 3:
        JS_GetElement(cx, array, 2, &jsZ);

        case 2:
        JS_GetElement(cx, array, 1, &jsY);
        JS_GetElement(cx, array, 0, &jsX);
    }

    if (JSVAL_IS_DOUBLE(jsX) || JSVAL_IS_DOUBLE(jsY) || JSVAL_IS_DOUBLE(jsZ) || JSVAL_IS_DOUBLE(jsW)) {
        jsdouble x, y, z, w;

        switch (length) {
            case 4:
            JS_ValueToNumber(cx, jsW, &w);

            case 3:
            JS_ValueToNumber(cx, jsZ, &z);

            case 2:
            JS_ValueToNumber(cx, jsY, &y);
            JS_ValueToNumber(cx, jsX, &x);
        }

        switch (length) {
            case 2: glVertex2d(x, y); break;
            case 3: glVertex3d(x, y, z); break;
            case 4: glVertex4d(x, y, z, w); break;
        }
    }
    else {
        int32 x, y, z, w;

        switch (length) {
            case 4:
            JS_ValueToInt32(cx, jsW, &w);

            case 3:
            JS_ValueToInt32(cx, jsZ, &z);

            case 2:
            JS_ValueToInt32(cx, jsY, &y);
            JS_ValueToInt32(cx, jsX, &x);
        }

        switch (length) {
            case 2: glVertex2i(x, y); break;
            case 3: glVertex3i(x, y, z); break;
            case 4: glVertex4i(x, y, z, w); break;
        }
    }

    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);
    return JS_TRUE;
}

JSBool
GL_color (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* array;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &array)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsuint length;
    JS_GetArrayLength(cx, array, &length);

    if (length < 3 || length > 4) {
        JS_ReportError(cx, "Wrong number of values.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval jsR, jsG, jsB, jsAlpha = JSVAL_VOID;

    switch (length) {
        case 4:
        JS_GetElement(cx, array, 3, &jsAlpha);

        case 3:
        JS_GetElement(cx, array, 2, &jsB);
        JS_GetElement(cx, array, 1, &jsG);
        JS_GetElement(cx, array, 0, &jsR);
    }

    if (JSVAL_IS_DOUBLE(jsR) || JSVAL_IS_DOUBLE(jsG) || JSVAL_IS_DOUBLE(jsB) || JSVAL_IS_VOID(jsAlpha)) {
        jsdouble r, g, b, alpha;

        switch (length) {
            case 4:
            JS_ValueToNumber(cx, jsAlpha, &alpha);

            case 3:
            JS_ValueToNumber(cx, jsB, &b);
            JS_ValueToNumber(cx, jsG, &g);
            JS_ValueToNumber(cx, jsR, &r);
        }

        switch (length) {
            case 3: glColor3d(r, g, b); break;
            case 4: glColor4d(r, g, b, alpha); break;
        }
    }
    else {
        int32 r, g, b, alpha;

        switch (length) {
            case 4:
            JS_ValueToInt32(cx, jsAlpha, &alpha);

            case 3:
            JS_ValueToInt32(cx, jsB, &b);
            JS_ValueToInt32(cx, jsG, &g);
            JS_ValueToInt32(cx, jsR, &r);
        }

        switch (length) {
            case 3: glColor3i(r, g, b); break;
            case 4: glColor4i(r, g, b, alpha); break;
        }
    }

    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);

    return JS_TRUE;
}

JSBool
GL_rotate (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* array;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &array)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsuint length;
    JS_GetArrayLength(cx, array, &length);

    if (length != 4) {
        JS_ReportError(cx, "Wrong number of values.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval element;
    jsdouble angle, x, y, z;

    JS_GetElement(cx, array, 0, &element); JS_ValueToNumber(cx, element, &angle);
    JS_GetElement(cx, array, 1, &element); JS_ValueToNumber(cx, element, &x);
    JS_GetElement(cx, array, 2, &element); JS_ValueToNumber(cx, element, &y);
    JS_GetElement(cx, array, 3, &element); JS_ValueToNumber(cx, element, &z);

    glRotated(angle, x, y, z);

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_OPERATION: errorText = "You can't call GL.rotate between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }


    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);
    return JS_TRUE;
}

JSBool
GL_translate (JSContext* cx, JSObject* object, uintN argc, jsval* argv, jsval* rval)
{
    JSObject* array;

    JS_BeginRequest(cx);
    JS_EnterLocalRootScope(cx);

    if (argc < 1 || !JS_ConvertArguments(cx, argc, argv, "o", &array)) {
        JS_ReportError(cx, "Not enough parameters.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsuint length;
    JS_GetArrayLength(cx, array, &length);

    if (length != 3) {
        JS_ReportError(cx, "Wrong number of values.");

        JS_LeaveLocalRootScope(cx);
        JS_EndRequest(cx);
        return JS_FALSE;
    }

    jsval element;
    jsdouble x, y, z;

    JS_GetElement(cx, array, 0, &element); JS_ValueToNumber(cx, element, &x);
    JS_GetElement(cx, array, 1, &element); JS_ValueToNumber(cx, element, &y);
    JS_GetElement(cx, array, 2, &element); JS_ValueToNumber(cx, element, &z);

    glTranslated(x, y, z);

    GLenum error = glGetError();
    if (error) {
        std::string errorText;

        switch (error) {
            case GL_INVALID_OPERATION: errorText = "You can't call GL.translate between GL.begin and GL.end."; break;
        }

        JS_ReportError(cx, (char*) errorText.c_str());
        return JS_FALSE;
    }

    JS_LeaveLocalRootScope(cx);
    JS_EndRequest(cx);
    return JS_TRUE;
}

