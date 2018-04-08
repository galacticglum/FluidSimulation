#version 450

in vec2 uv;
out vec4 fragColour;

uniform sampler2D velocity;
uniform sampler2D source;
uniform vec2 texelSize;
uniform float dt;
uniform float dissipation;

void main()
{
    vec2 coord = uv - dt * texture2D(velocity, uv).xy * texelSize;
    fragColour = dissipation * texture2D(source, coord);
    fragColour.a = 1.0;
}