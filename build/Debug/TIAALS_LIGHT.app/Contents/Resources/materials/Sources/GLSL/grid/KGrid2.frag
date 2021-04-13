

uniform vec2 resolution;
uniform vec2 gridInterval;
uniform float sw;
uniform float alpha;
void main()
{
    vec2 offset = vec2(1.0, 1.0);
    vec2 st = vec2((gl_FragCoord.x / resolution.x), offset.y - (gl_FragCoord.y / resolution.y));
    vec2 st2 = st;
    vec4 color = vec4(0.0, 0.0, 0.0, alpha);

    st *= vec2(resolution.x / gridInterval.x , resolution.y / gridInterval.x);
    st = fract(st);
    
    if(st.x > 0.9 || st.y > 0.9){
        gl_FragColor = vec4(0.0,0.0,0.0,alpha);
    }else{
        gl_FragColor = vec4(0.0,0.0,0.0,0.0);

    }
}
