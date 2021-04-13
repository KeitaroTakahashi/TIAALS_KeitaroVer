
uniform vec2 resolution;
uniform sampler2D buffer;
uniform vec2 dataSize;
uniform float mag;

vec3 rgb2hsb( in vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix (vec4(c.bg, K.wz),
                  vec4(c.gb, K.xy),
                  step(c.b, c.g));
    vec4 q = mix (vec4(p.xyw, c.r),
                  vec4(c.r, p.yzx),
                  step(p.x, c.r));
    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)),
                d / (q.x + e),
                q.x);
}

vec3 hsb2rgb( in vec3 c)
{
    vec3 rgb = clamp(abs(mod(c.x * 6.0 + vec3(0.0, 4.0, 2.0), 6.0) -3.0)
                     -1.0,
                     0.0,
                     1.0);
    
    rgb = rgb * rgb * (3.0 - 2.0 * rgb);
    return c.z * mix(vec3(1.0), rgb, c.y);
}


vec3 hsb2rgb2(in vec3 c, in vec2 st)
{
    float threshold = 0.83333333333;
    float ratio = 1.0 / (1.0 - threshold);
    
    vec2 st_inverse = 1.0 - st;
    //float fadeOut = step(0.0, st.x - threshold) * (st.x - threshold);
    float fadeOut = step(0.0, c.x - threshold) * (c.x - threshold) * ratio;
    
    vec3 colorA = hsb2rgb(vec3(c.x, c.y, smoothstep(c.z, 0.0, fadeOut)));
    vec3 colorB = hsb2rgb(vec3(c.x, c.y, c.z));
    
    float s = step(0.8, c.x);
    
    return colorA * s + colorB * (1.0 - s);
    
}

void main()
{
    // st x and y = 0.0 - 1.0
    vec2 st = gl_FragCoord.xy / resolution.xy;
    //vec4 color = texture2D(buffer, st);
    
    vec2 index = st * dataSize;
    vec2 i = floor(index);
    vec2 f = fract(index);
    
    vec4 color0 = vec4(0.0);
    vec4 color1 = vec4(0.0);
    vec4 color2 = vec4(0.0);
    vec4 color3 = vec4(0.0);
    
    vec2 next = (i + 1.0) / dataSize;
    
    // target color
    color0 = texture2D(buffer, st);
    color1 = texture2D(buffer, vec2(next.x, st.y));
    color2 = texture2D(buffer, next);
    color3 = texture2D(buffer, vec2(st.x, next.y));
    
    // fix next color
    if(i.x == (dataSize.x -1.0))
    {
        color1 = color0;
        color2 = color3;
    }
    
    // fix above color
    if(i.y == (dataSize.y - 1.0))
    {
        color2 = color1;
        color3 = color0;
    }
    
    vec4 color = vec4(
                      mix(
                          vec3(mix(color0.rgb, color3.rgb, f.y)),
                          vec3(mix(color1.rgb, color2.rgb, f.y)),
                          f.x),
                      1.0);
    
    color = vec4(hsb2rgb2(vec3((1.0 - color.r * mag), 1.0, 1.0), st), 1.0);
    
    vec4 colorTex = texture2D(buffer, st);
    gl_FragColor = color;
}
