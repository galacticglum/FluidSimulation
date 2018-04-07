attribute vec2 position;
attribute vec2 uv;
attribute vec2 L;
attribute vec2 R;
attribute vec2 T;
attribute vec2 B;
uniform vec2 texelSize;

void main()
{
    uv = position * 0.5 + 0.5;
    L = uv - vec2(texelSize.x, 0.0);
    R = uv + vec2(texelSize.x, 0.0);
    T = uv + vec2(0.0, texelSize.y);
    B = uv - vec2(0.0, texelSize.y);

    gl_Position = vec4(position, 0.0, 1.0);
}