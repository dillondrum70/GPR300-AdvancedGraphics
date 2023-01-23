#version 450

out vec4 FragColor;

in vec4 Color;

uniform float _Time;

void main(){
	float t = (sin(_Time * 6) + 1) / 2;
	FragColor = Color * t;
}