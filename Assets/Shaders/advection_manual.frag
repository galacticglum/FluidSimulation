precision highp float;
precision mediump sampler2D;

varying vec2 uv;
uniform sampler2D velocity;
uniform sampler2D source;
uniform vec2 texelSize;
uniform float dt;
uniform float dissipation;

vec4 bilerp(in sampler2D sample, in vec2 p)
{
    vec4 st;
    st.xy = floor(p - 0.5) + 0.5;
    st.zw = st.xy + 1.0;
    
    vec4 uv = st * texelSize.xyxy;
    vec4 a = texture2D(sample, uv.xy);
    vec4 b = texture2D(sample, uv.zy);
    vec4 c = texture2D(sample, uv.xw);
    vec4 d = texture2D(sample, uv.zw);

    vec2 f = p - st.xy;
    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y); 
}

void main()
{
    vec2 coord = gl_FragCoord.xy - dt * texture2D(velocity, uv).xy;
    gl_FragColor = dissipation * bilerp(source, coord);
    gl_FragColor.a = 1.0;
}