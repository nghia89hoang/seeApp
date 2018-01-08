#version 100
precision mediump float;
/*
 *
 *  Peter R. Elespuru
 *
 *  modified from:
 *  http://coding-experiments.blogspot.com/2010/10/thermal-vision-pixel-shader.html
 */

uniform sampler2D uTex0;
varying vec2 TexCoord0;
void main(void) {
    
    vec4 pixcol = texture2D(uTex0, TexCoord0.xy);
    vec4 colors[3];
    colors[0] = vec4(0.,0.,1.,1.);
    colors[1] = vec4(1.,1.,0.,1.);
    colors[2] = vec4(1.,0.,0.,1.);
    //float lum = (pixcol.r+pixcol.g+pixcol.b)/3.;
    // better shadow range
    float lum = dot(vec3(0.30, 0.59, 0.11), pixcol.rgb);
    int ix = (lum < 0.5)? 0:1;
    vec4 thermal = mix(colors[ix],colors[ix+1],(lum-float(ix)*0.5)/0.5);
    gl_FragColor = thermal;
    
}
