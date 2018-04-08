#version 450

in vec2 uv;
in vec2 L;
in vec2 R;
in vec2 T;
in vec2 B;
out vec4 fragColour;

uniform sampler2D velocity;

vec2 sampleVelocity(in vec2 uv)
{
    vec2 multiplier = vec2(1.0, 1.0);
    if(uv.x < 0.0)
    {
        uv.x = 0.0;
        multiplier.x = -1.0;
    }

    if(uv.x > 1.0)
    {
        uv.x = 1.0;
        multiplier.x = -1.0;
    }

    if(uv.y < 0.0)
    {
        uv.y = 0.0;
        multiplier.y = -1.0;
    }

    if(uv.y > 1.0)
    {
        uv.y = 1.0;
        multiplier.y = -1.0;
    }

    return multiplier * texture2D(velocity, uv).xy;
}

void main()
{
    float velocityL = sampleVelocity(L).x;
    float velocityR = sampleVelocity(R).x;
    float velocityT = sampleVelocity(T).y;
    float velocityB = sampleVelocity(B).y;
    float div = 0.5 * (velocityR - velocityL + velocityT - velocityB);
    
    fragColour = vec4(div, 0.0, 0.0, 1.0);
}