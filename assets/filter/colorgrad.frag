#version 100
precision mediump float;

varying highp vec2 TexCoord0;
uniform sampler2D uTex0;

void main(void) {
    highp vec4 tex = texture2D(uTex0, TexCoord0);
    vec4 color = vec4(TexCoord0.x, TexCoord0.y, (TexCoord0.x + TexCoord0.y) * 0.5, 1.0);
    gl_FragColor = color * 0.4 + tex * 0.6;
}
