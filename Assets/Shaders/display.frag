#version 450

in vec2 uv;
out vec4 fragColour;

uniform sampler2D texture;

void main () 
{
    //texture2D(texture, uv) * 
    fragColour = texture2D(texture, uv);//vec4(1, 0, 0, 1);
}