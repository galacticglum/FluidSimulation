precision highp float;
precision mediump sampler2D;

varying vec2 uv;
varying vec2 L;
varying vec2 R;
varying vec2 T;
varying vec2 B;
uniform sampler2D pressure;
uniform sampler2D divergence;

vec2 bounds(int vec2 uv)
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
    float div = texture2D(divergence, uv).x;
    float p = (pressureL + pressureR + pressureB + presureT - div) * 0.25;
    gl_FragColor = vec4(pressure, 0.0, 0.0, 1.0);
}