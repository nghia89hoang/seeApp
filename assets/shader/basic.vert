#version 100

attribute vec4 ciPosition;
attribute vec4 ciTexCoord0;

uniform mat4 ciModelViewProjection;

varying highp vec2 TexCoord0;

void main(void) {
    TexCoord0 = ciTexCoord0.st;
    gl_Position = ciModelViewProjection * ciPosition;
}
