#version 100
precision mediump float;
// Dilation
// maximum of 3x3 kernel

varying highp vec2          TexCoord0;
uniform sampler2D           uTex0;
uniform highp vec2          uTexSize;

//vec4 sample(float dx,float dy)
//{
//   return texture2D(uTex0,TexCoord0.st+vec2(dx,dy));
//}

highp vec4 sample(float dx, float dy) {
    vec2 nc = TexCoord0 + vec2(dx, dy);
    if(nc.x > 0.0 && nc.y > 0.0) {
        return texture2D(uTex0, nc);
    } else {
        return texture2D(uTex0, TexCoord0);
    }
}
void main(void)
{
    float dX = 1.0 / uTexSize.x;
    float dY = 1.0 / uTexSize.y;
    vec4 color = sample(0.0,0.0);
    color = min(color , sample(-dX,+dY));
    color = min(color , sample(0.0,+dY));
    color = min(color , sample(+dX,+dY));
    color = min(color , sample(-dX,0.0));
    color = min(color , sample(+dX,0.0));
    color = min(color , sample(-dX,-dY));
    color = min(color , sample(0.0,-dY));
    color = min(color , sample(+dX,-dY));
    gl_FragColor = color;
}

