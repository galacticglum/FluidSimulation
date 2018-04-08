#version 450

in vec2 uv;
out vec4 fragColour;

uniform sampler2D target;
uniform float aspectRatio;
uniform vec3 colour;
uniform vec2 point;
uniform float radius;

void main()
{
    vec2 p = uv - point.xy;
    p.x *= aspectRatio;

    vec3 splat = exp(-dot(p, p) / radius) * colour;
    vec3 base = texture2D(target, uv).xyz;
    fragColour = vec4(base + splat, 1.0);
}