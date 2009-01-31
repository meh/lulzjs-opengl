require("OpenGL/GL");
require("OpenGL/GLUT");

OpenGL.GLUT.init(arguments);
OpenGL.GLUT.displayMode = (
      GLUT.DisplayMode.Double 
    | GLUT.DisplayMode.RGBA
    | GLUT.DisplayMode.Alpha
    | GLUT.DisplayMode.Depth
);

var window = new GLUT.Window({x: 0, y: 0, width: 640, height: 480});

window.onResize = function (width, height) {
    if (height < 0 || width < 0) {
        return;
    }

    GL.viewport(0, 0, width, height);
};

window.display = window.onIdle = function () {
    GL.clear(GL.Buffers.Color | GL.Buffers.Depth);
};

window.onKey = function (key, x, y) {
    if (key == GLUT.Keys.Escape) {
        window.destroy();
        exit();
    }
};

