#version 450

out vec4 FragColor;

in vec4 Color;

uniform float _Time;

void main(){
	float t = abs(sin(_Time));
	FragColor = Color * t;
}