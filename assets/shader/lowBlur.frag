#version 100
precision mediump float;
// Blur (low-pass)
//   1 2 1
//   2 1 2   / 13
//   1 2 1

uniform vec2        uTexSize;
uniform sampler2D   uTex0;
varying highp vec2  TexCoord0;
vec4 sample(float dx,float dy)
{
    return texture2D(uTex0,TexCoord0.st+vec2(dx,dy));
}

void main()
{
    float one = 1.0/13.0;
    float two = 2.0/13.0;
    float dX = 1.0 / uTexSize.x;
    float dY = 1.0 / uTexSize.y;
    gl_FragColor = one*sample(-dX,+dY) + two*sample(0.0,+dY) + one*sample(+dX,+dY)
    + two*sample(-dX,0.0) + one*sample(0.0,0.0) + two*sample(+dX,0.0)
    + one*sample(-dX,-dY) + two*sample(0.0,-dY) + one*sample(+dX,-dY);
}
