#version 100
precision mediump float;
/*
 *
 *  Peter R. Elespuru
 *
 *  modified from:
 *  http://cpansearch.perl.org/src/CORION/App-VideoMixer-0.02/filters/
 */

uniform sampler2D uTex0;
varying vec2 TexCoord0;

void main(void) {
    float frequency = 150.0;
    float offset = 2.0;
    
    float global_pos = (TexCoord0.y + offset) * frequency;
    float wave_pos = cos((fract( global_pos ) - 0.5)*3.14);
    vec4 pel = texture2D( uTex0, TexCoord0 );
    
    gl_FragColor = mix(vec4(0,0,0,0), pel, wave_pos);
}
