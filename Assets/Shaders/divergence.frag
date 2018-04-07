precision highp float;
precision mediump sampler2D;

varying vec2 uv;
varying vec2 L;
varying vec2 R;
varying vec2 T;
varying vec2 B;
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
    gl_FragColor = vec4(div, 0.0, 0.0, 1.0);
}