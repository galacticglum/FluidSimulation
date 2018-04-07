varying vec2 uv;
varying sampler2D velocity;
varying sampler2D source;
varying vec2 texelSize;
uniform float dt;
uniform float dissipation;

void main()
{
    vec2 coord = uv - dt * texture2D(velocity, uv).xy * texelSize;
    gl_FragColor = dissipation * texture2D(source, coord);
    gl_FragColor.a = 1.0;
}