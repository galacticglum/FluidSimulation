#version 450

in vec2 uv;
in vec2 L;
in vec2 R;
in vec2 T;
in vec2 B;
out vec4 fragColour;

uniform sampler2D velocity;

void main()
{
    float velocityL = texture2D(velocity, L).y;
    float velocityR = texture2D(velocity, R).y;
    float velocityT = texture2D(velocity, T).x;
    float velocityB = texture2D(velocity, B).x;

    float v = velocityR - velocityL - velocityT + velocityB;
    fragColour = vec4(v, 0.0, 0.0, 1.0);
}