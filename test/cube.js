#! /usr/bin/env ljs
require("OpenGL/GL");
require("OpenGL/GLU");
require("OpenGL/GLUT");

GLUT.init(arguments, GLUT.DisplayModes.Double|GLUT.DisplayModes.RGB|GLUT.DisplayModes.Dept);

vertices = [
    [-1.0,-1.0,-1.0], [1.0,-1.0,-1.0], [1.0,1.0,-1.0],
    [-1.0, 1.0,-1.0], [-1.0,-1.0,1.0], [1.0,-1.0,1.0],
    [ 1.0, 1.0, 1.0], [-1.0, 1.0,1.0]
];

normals = [
    [-1.0,-1.0,-1.0], [1.0,-1.0,-1.0], [1.0,1.0,-1.0],
    [-1.0, 1.0,-1.0], [-1.0,-1.0,1.0], [1.0,-1.0,1.0],
    [ 1.0, 1.0, 1.0], [-1.0, 1.0,1.0]
];

colors = [
    [0.0,0.0,0.0], [1.0,0.0,0.0], [1.0,1.0,0.0],
    [0.0,1.0,0.0], [0.0,0.0,1.0], [1.0,0.0,1.0],
    [1.0,1.0,1.0], [0.0,1.0,1.0]
];

function polygon (a, b, c, d)
{
    GL.begin(GL.Primitives.Polygon);
        GL.color(colors[a]);
        GL.normal(normals[a]);
        GL.vertex(vertices[a]);
        
        GL.color(colors[b]);
        GL.normal(normals[b]);
        GL.vertex(vertices[b]);

        GL.color(colors[c]);
        GL.normal(normals[c]);
        GL.vertex(vertices[c]);
        
        GL.color(colors[d]);
        GL.normal(normals[d]);
        GL.vertex(vertices[d]);
    GL.end();
}

function colorCube ()
{
    polygon(0,3,2,1);
    polygon(2,3,7,6);
    polygon(0,4,7,3);
    polygon(1,2,6,5);
    polygon(4,5,6,7);
    polygon(0,1,5,4);
}

theta  = [0.0, 0.0, 0.0];
axis   = 2;
viewer = [0.0, 0.0, 5.0];

var window = new GLUT.Window({title: "lulzJS OpenGL test", width: 640, height: 480}, {
    onDisplay: function () {
        GL.clear(GL.Buffers.Color|GL.Buffers.Depth);
        GL.loadIdentity();
        GLU.lookAt({eye: viewer, up: [0, 1, 0]});

        GL.rotate([theta[0], 1.0, 0.0, 0.0]);
        GL.rotate([theta[1], 0.0, 1.0, 0.0]);
        GL.rotate([theta[2], 0.0, 0.0, 1.0]);

        colorCube();

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

GL.enable(GL.Capabilities.DepthTest);

GLUT.mainLoop();
