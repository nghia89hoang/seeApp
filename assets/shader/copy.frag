#version 100

varying highp vec2 TexCoord0;

uniform sampler2D uTex0;

void main(void) {
    highp vec4 color = texture2D(uTex0, TexCoord0);
    gl_FragColor = color;
    
}
