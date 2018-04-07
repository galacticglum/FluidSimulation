varying vec2 uv;
varying vec2 L;
varying vec2 R;
varying vec2 T;
varying vec2 B;

uniform sampler2D pressure;
uniform sampler2D velocity;

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
    vec2 vel = texture2D(velocity, uv).x;
    vel.xy -= vec2(pressureR - pressureL, presureT - pressureB);
    gl_FragColor = vec4(vel, 0.0, 1.0);
}