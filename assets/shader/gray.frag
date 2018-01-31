#version 100

varying highp vec2 TexCoord0;

uniform sampler2D uTex0;

void main(void) {
    highp vec4 color = texture2D(uTex0, TexCoord0);
    highp float grayLevel = 0.59 * color.r + 0.11 * color.g + 0.3 * color.b;
    gl_FragColor = vec4( vec3(grayLevel), color.a );
}
