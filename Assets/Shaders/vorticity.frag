precision highp float;
precision mediump sampler2D;

varying vec2 uv;
varying vec2 T;
varying vec2 B;
uniform sampler2D velocity;
uniform sampler2D curl;
uniform float curl;
uniform float dt;

void main()
{
    float curlT = texture2D(curl, T).x;
    float curlB = texture2D(curl, B).x;
    float curlC = texture2D(curl, uv).x;
    vec2 force = vec2(abs(curlT) - abs(curlB), 0.0);
    force *= 1.0 / length(force + 0.00001) * curl * curlC;
    vec2 vel = texture2D(velocity, uv).xy;
    gl_FragColor = vec4(vel + force * dt, 0.0, 1.0);
}