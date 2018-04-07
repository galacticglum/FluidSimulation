precision highp float;
precision mediump sampler2D;

varying vec2 uv;
varying sampler2D texture;
uniform float value;

void main() 
{
    gl_FragColor = value * texture2D(texture, uv);
}