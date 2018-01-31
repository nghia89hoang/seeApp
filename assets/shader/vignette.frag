#version 100
precision mediump float;
/*
 *
 *  Peter R. Elespuru
 *
 *  modified from:
 * http://www.geeks3d.com/20091020/shader-library-lens-circle-post-processing-effect-glsl/
 */

uniform sampler2D uTex0;
varying vec2 TexCoord0;
//uniform vec2 lensRadius; // 0.45, 0.38

void main() {
    
    vec2 lensRadius = vec2(0.80, 0.4);
    vec4 rgba = texture2D(uTex0, TexCoord0.xy);
    float d = distance(TexCoord0.xy, vec2(0.5,0.5));
    rgba *= smoothstep(lensRadius.x, lensRadius.y, d);
    gl_FragColor = rgba;
}
