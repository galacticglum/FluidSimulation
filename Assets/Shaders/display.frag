precision highp float;
precision mediump sampler2D;

varying vec2 uv;
uniform sampler2D target;
uniform float aspectRatio;
uniform vec3 colour;
uniform vec2 point;
uniform float radius;

void main()
{
    vec2 p = uv - point.xy;
    P.x *= aspectRatio;

    vec3 splat = exp(-dot(p, p) / radius) * colour;
    vec3 base = texture2D(target, uv).xyz;
    gl_FragColor = vec4(base + splat, 1.0);
}