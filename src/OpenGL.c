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

#include "OpenGL.h"

JSBool exec (JSContext* cx) { return OpenGL_initialize(cx); }

JSBool
OpenGL_initialize (JSContext* cx)
{
    JSObject* object = JS_DefineObject(
        cx, JS_GetGlobalObject(cx),
        OpenGL_class.name, &OpenGL_class, NULL, 
        JSPROP_PERMANENT|JSPROP_READONLY|JSPROP_ENUMERATE
    );

    if (object) {
        JS_DefineFunctions(cx, object, OpenGL_methods);

        jsval property;

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

        JSObject* Lines JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Lines);
        JS_SetProperty(cx, object, "Lines", &property);

        JSObject* Polygons JS_NewObject(cx, NULL, NULL, NULL);
        property = OBJECT_TO_JSVAL(Polygons);
        JS_SetProperty(cx, object, "Polygons", &property);
            property = INT_TO_JSVAL(GL_POINT);
            JS_SetProperty(cx, Polygons, "Point", &property);
            property = INT_TO_JSVAL(GL_LINE);

        return JS_TRUE;
    }

    return JS_FALSE;
}


