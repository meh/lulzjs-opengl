#! /usr/bin/env ljs
require("OpenGL/GL");
require("OpenGL/GLU");
require("OpenGL/GLUT");

GLUT.init(arguments, GLUT.DisplayModes.Double|GLUT.DisplayModes.RGB|GLUT.DisplayModes.Dept);

var window = new GLUT.Window({title: "lulzJS OpenGL test", width: 640, height: 480}, {
    onDisplay: function () {
        GL.clear(GL.Buffers.Color|GL.Buffers.Depth);
        GL.loadIdentity();

//        GL.translate([0.0, 0.0, -6.0]);

        GL.begin(GL.Primitives.Quad);
            GL.color([0xFF, 0x00, 0x00]);
            GL.vertex([-0.2, 0.2, 0.0]);
            GL.vertex([ 0.2, 0.2, 0.0]);
            GL.vertex([ 0.2,-0.2, 0.0]);
            GL.vertex([-0.2,-0.2, 0.0]);
        GL.end();

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

GL.enable(GL.Capabilities.DepthTest);
//GLU.perspective({field: 45, aspect: window.Size.Width/window.Size.Height, near: 0.1, far: 100});

GLUT.mainLoop();
