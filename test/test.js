#! /usr/bin/env ljs
require("OpenGL/GL");
require("OpenGL/GLU");
require("OpenGL/GLUT");

GLUT.init(arguments, GLUT.DisplayModes.Double|GLUT.DisplayModes.RGB|GLUT.DisplayModes.Dept);

var window = new GLUT.Window({title: "lulzJS OpenGL test", width: 640, height: 480}, {
    onDisplay: function () {
        GL.clear(GL.Buffers.Color|GL.Buffers.Depth);

        GL.begin(GL.Primitives.Polygon);
            GL.vertex([-1.0, -1.0, -1.0]);
            GL.vertex([-1.0,  1.0, -1.0]);
            GL.vertex([ 1.0,  1.0, -1.0]);
            GL.vertex([ 1.0, -1.0, -1.0]);
        GL.end();

        GL.flush();
        GLUT.swapBuffers();
    },

    onKey: function (key, x, y) {
        if (key == GLUT.Keys.Escape) {
            exit(0);
        }
    },

    Mouse: {
        onClick: function (button, x, y) {

        }
    }
});

GLUT.mainLoop();
