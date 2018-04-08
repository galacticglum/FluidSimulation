#version 450

layout (location = 0) in vec2 vertexPosition;

out vec2 uv;
out vec2 L;
out vec2 R;
out vec2 T;
out vec2 B;

uniform vec2 texelSize;

void main()
{
    uv = vertexPosition * 0.5 + 0.5;
    L = uv - vec2(texelSize.x, 0.0);
    R = uv + vec2(texelSize.x, 0.0);
    T = uv + vec2(0.0, texelSize.y);
    B = uv - vec2(0.0, texelSize.y);

    gl_Position = vec4(vertexPosition, 0.0, 1.0);
}