#! /usr/bin/env ljs
require("OpenGL/GL");
require("OpenGL/GLUT");

GLUT.init(arguments, GLUT.DisplayModes.Double|GLUT.DisplayModes.RGB|GLUT.DisplayModes.Dept);

var window = new GLUT.Window({title: "lulzJS OpenGL test", width: 800, height: 600}, {
    onDisplay: function () {
        GL.clear(GL.Buffers.Color|GL.Buffers.Depth);
        GL.flush();
        GLUT.swapBuffers();
    }
});

GLUT.mainLoop();
