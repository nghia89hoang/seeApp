#version 100
precision mediump float;
/*
 *
 *  Peter R. Elespuru
 *
 *  modified from:
 *  http://www.forceflow.be/thesis/thesis-code/
 */
varying vec2 TexCoord0;
uniform sampler2D uTex0;
uniform vec2        uTexSize;
float intensity(in vec4 color)
{
    return sqrt((color.r*color.r)+(color.g*color.g)+(color.b*color.b));
}

vec3 sobel(float step, vec2 center)
{
    float limit = 0.2;
    int width = 600;
    
    // get samples around pixel
    float tleft = intensity(texture2D(uTex0,center + vec2(-step,step)));
    float left = intensity(texture2D(uTex0,center + vec2(-step,0)));
    float bleft = intensity(texture2D(uTex0,center + vec2(-step,-step)));
    float top = intensity(texture2D(uTex0,center + vec2(0,step)));
    float bottom = intensity(texture2D(uTex0,center + vec2(0,-step)));
    float tright = intensity(texture2D(uTex0,center + vec2(step,step)));
    float right = intensity(texture2D(uTex0,center + vec2(step,0)));
    float bright = intensity(texture2D(uTex0,center + vec2(step,-step)));
    
    // Sobel masks (to estimate gradient)
    //        1 0 -1     -1 -2 -1
    //    X = 2 0 -2  Y = 0  0  0
    //        1 0 -1      1  2  1
    
    float x = tleft + 2.0*left + bleft - tright - 2.0*right - bright;
    float y = -tleft - 2.0*top - tright + bleft + 2.0 * bottom + bright;
    float color = sqrt((x*x) + (y*y));
    if (color < limit){return vec3(0.0,0.0,0.0);}
    return vec3(1.0,1.0,1.0);
}

void main(void)
{
    gl_FragColor = vec4(1,1,1,1);
    float step = 1.0/uTexSize.x;
    vec2 center = TexCoord0.st;
    gl_FragColor.xyz = sobel(step,center);
}
