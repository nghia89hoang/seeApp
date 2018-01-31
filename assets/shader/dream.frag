#version 100
precision mediump float;
/*
 *
 *  Peter R. Elespuru
 *
 *  modified from this idea:
 *  http://www.geeks3d.com/20091112/shader-library-dream-vision-post-processing-filter-glsl/
 */

varying highp vec2 TexCoord0;
uniform sampler2D uTex0;

void main (void) {
    vec4 c = texture2D(uTex0, TexCoord0);
    
    c += texture2D(uTex0, TexCoord0+0.001);
    c += texture2D(uTex0, TexCoord0+0.003);
    c += texture2D(uTex0, TexCoord0+0.005);
    c += texture2D(uTex0, TexCoord0+0.007);
    c += texture2D(uTex0, TexCoord0+0.009);
    c += texture2D(uTex0, TexCoord0+0.011);
    
    c += texture2D(uTex0, TexCoord0-0.001);
    c += texture2D(uTex0, TexCoord0-0.003);
    c += texture2D(uTex0, TexCoord0-0.005);
    c += texture2D(uTex0, TexCoord0-0.007);
    c += texture2D(uTex0, TexCoord0-0.009);
    c += texture2D(uTex0, TexCoord0-0.011);
    
//    c.rgb = vec3((c.r+c.g+c.b)/3.0);
//    c = c / 9.5;
    c = c / 10.5;
    gl_FragColor = c;
    
}
