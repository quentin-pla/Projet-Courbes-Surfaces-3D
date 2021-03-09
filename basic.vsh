attribute highp vec4 posAttr;
attribute lowp  vec4 colAttr;
varying lowp  vec4 col;
uniform highp mat4 projMatrix;
uniform highp mat4 mvMatrix;

void main() {
   col = colAttr;
   gl_Position = projMatrix * mvMatrix * posAttr;
}

