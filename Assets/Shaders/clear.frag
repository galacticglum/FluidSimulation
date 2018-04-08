#version 450

in vec2 uv;
out vec4 fragColour;

uniform sampler2D texture;
uniform float value;

void main() 
{
    fragColour = value * texture2D(texture, uv);
}