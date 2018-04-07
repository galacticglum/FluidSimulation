precision highp float;
precision mediump sampler2D;

varying vec2 uv;
varying vec2 L;
varying vec2 R;
varying vec2 T;
varying vec2 B;
uniform sampler2D velocity;

void main()
{
    float velocityL = texture2D(velocity, L).y;
    float velocityR = texture2D(velocity, R).y;
    float velocityT = texture2D(velocity, T).x;
    float velocityB = texture2D(velocity, B).x;

    float v = velocityR - velocityL - velocityT + velocityB;
    gl_FragColor = vec4(v, 0.0, 0.0, 1.0);
}