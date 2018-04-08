#version 450

in vec2 uv;
in vec2 L;
in vec2 R;
in vec2 T;
in vec2 B;
out vec4 fragColour;

uniform sampler2D pressure;
uniform sampler2D divergence;

vec2 bounds(in vec2 uv)
{
    uv = min(max(uv, 0.0), 1.0);
    return uv;
}

void main()
{
    float pressureL = texture2D(pressure, bounds(L)).x;
    float pressureR = texture2D(pressure, bounds(R)).x;
    float presureT = texture2D(pressure, bounds(T)).x;
    float pressureB = texture2D(pressure, bounds(B)).x;
    float pressureUv = texture2D(pressure, uv).x;
    float dv = texture2D(divergence, uv).x;
    float p = (pressureL + pressureR + pressureB + presureT - dv) * 0.25;

    fragColour = vec4(p, 0.0, 0.0, 1.0);
}