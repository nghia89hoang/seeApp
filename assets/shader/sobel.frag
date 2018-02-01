#version 100
precision mediump float;
// Sobel edge detection
//    -1 -2 -1       1 0 -1
// H = 0  0  0   V = 2 0 -2
//     1  2  1       1 0 -1
//
// result = sqrt(H^2 + V^2)

varying highp vec2  TexCoord0;

uniform sampler2D   uTex0;
uniform highp vec2        uTexSize;
highp vec4 sample(float dx, float dy) {
    vec2 nc = TexCoord0 + vec2(dx, dy);
    if(nc.x > 0.0 && nc.y > 0.0) {
        return texture2D(uTex0, nc);
    } else {
        return texture2D(uTex0, TexCoord0);
    }
}
void main(void) {
//    highp vec2 texSize = textureSize(uTex0, 0);
    highp vec2 texSize = uTexSize;
    highp float dx = 1.0 / texSize.x;
    highp float dy = 1.0 / texSize.y;
    vec4 e00 = sample(-dx, -dy);
    vec4 e01 = sample(0.0, -dy);
    vec4 e02 = sample( dx, -dy);
    vec4 e03 = sample(-dx, 0.0);
    vec4 e04 = sample(0.0, 0.0);
    vec4 e05 = sample( dx, 0.0);
    vec4 e06 = sample(-dx,  dy);
    vec4 e07 = sample(0.0,  dy);
    vec4 e08 = sample( dx,  dy);
    vec4 H =   -e01 - (2.0*e02) - e03 +
                e06 + (2.0*e07) + e08;
    vec4 V =    e00 + (2.0*e03) + e06 -
                e02 - (2.0*e05) - e08;
    float r = 0.0 + sqrt(H.r*H.r + V.r*V.r);
    float g = 0.0 + sqrt(H.g*H.g + V.g*V.g);
    float b = 0.0 + sqrt(H.b*H.b + V.b*V.b);
//    gl_FragColor = vec4(r,g,b,1.0) * 0.6 + e04 * 1.6;
    gl_FragColor = vec4(r,g,b,1.0);// * 0.6 + e04 * 1.6;
//    vec4 h1 = sample(-dx,-dy) + 2.0*sample(0.0, -dy) + sample( dx,-dy);
//    vec4 h2 = (sample(-dx, dy) + 2.0*sample(0.0,  dy) + sample( dx, dy));
//    gl_FragColor = e06 + (2.0*e07) + e08;
}
