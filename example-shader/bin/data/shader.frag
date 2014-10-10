//  Created by Patricio Gonzalez Vivo on 10/10/14.
//
//

uniform sampler2DRect colorTex;	// 	Color Buffer
uniform sampler2DRect depthTex;	//	Depth Buffer

float offset = 0.59;
float flatPct = 0.87;
float pct = 1.0;

float focalDistance = 0.15;
float focalRange = 0.14;

float getIntensity(vec2 u){
	vec3 a = texture2DRect(colorTex,u).xyz;
	return (a.x+a.y+a.z)/3.0;
}

float LinearizeDepth(float zoverw){
    float n = 1.0;
    float f = 20000.0;
    return (2.0 * n) / (f + n - zoverw * (f - n));
}

float FocalValue(vec2 pos){
    float depth = LinearizeDepth( texture2DRect(depthTex, pos).r ) * 20000.;
    float value = abs(depth  - (focalDistance*10000.) ) / (focalRange*20000.);
    return min( value , 1.0);
}

void main(){
	vec2 uv = gl_TexCoord[0].st;
	vec2 p = vec2(offset);
	
	float rangeTexel = FocalValue(gl_TexCoord[0].st);

	float avg = 0.0;
	avg += FocalValue(uv+vec2(p.x,0.0));
	avg += FocalValue(uv+vec2(-p.x,0.0));
	avg += FocalValue(uv+vec2(0.0,p.y));
	avg += FocalValue(uv+vec2(0.0,-p.y));
	avg += FocalValue(uv+vec2(p.x,p.y));
	avg += FocalValue(uv+vec2(-p.x,-p.y));
	avg += FocalValue(uv+vec2(p.x,-p.y));
	avg += FocalValue(uv+vec2(-p.x,p.y));
	avg /= 8.0;

	float focalPoint = 1.0-FocalValue(uv);
	float result = (focalPoint) + avg;
	result = (1.0-result)*(1000.0*pct);

    gl_FragColor.rgb = vec3(1.-result)-vec3((getIntensity(uv))*flatPct);
    gl_FragColor.a = 1.0;
}