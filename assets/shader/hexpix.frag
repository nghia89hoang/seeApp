#version 100
precision mediump float;
/*
*
*  Peter R. Elespuru
*  
*  Derived from:
*  http://coding-experiments.blogspot.com/2010/06/pixelation.html 
*/

varying vec2        TexCoord0;
uniform vec2        uTexSize;
uniform sampler2D   uTex0;

vec2 hexCoord(vec2 hexIndex) {

float H = 0.01;
float S = ((3./2.) * H/sqrt(3.));

int i = int(hexIndex.x);
int j = int(hexIndex.y);
vec2 r = vec2(0,0);
r.x = float(i) * S;
r.y = float(j) * H + mod(float(i),2.0) * H/2.0;
return r;

}

vec2 hexIndex(vec2 coord) {

float H = 0.01;
float S = ((3./2.) * H/sqrt(3.));

vec2 r;
float x = coord.x;
float y = coord.y;
float it = (floor(x/S));
float yts = y - mod(float(it),2.0) * H/2.;
float jt = (floor((1./H) * yts));
float xt = x - float(it) * S;
float yt = yts - float(jt) * H;
int deltaj = (yt > H/2.)? 1:0;
float fcond = S * (2./3.) * abs(0.5 - yt/H);

if (xt > fcond) {
r.x = it;
r.y = jt;

} else {
r.x = it - 1.0;
r.y = float(jt) - mod(float(r.x),2.0) + float(deltaj);

}

return r;
}

void main(void)
{
vec2 xy = TexCoord0.xy;
vec2 hexIx = hexIndex(xy);
vec2 hexXy = hexCoord(hexIx);
vec4 fcol = texture2D(uTex0, hexXy);
gl_FragColor = fcol;
}
