#version 450

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec4 vColor;

out vec4 Color;

uniform float _Time;

void main(){
	Color = vColor;

	float y = 0;

	if(vPos.x > 0)
	{
		y = sin(_Time) * vPos.y;
	}
	else{
		y = cos(_Time) * vPos.y;
	}
	gl_Position = vec4(vPos.x, y, vPos.z, 1.0);
}