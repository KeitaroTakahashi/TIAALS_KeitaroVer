
uniform vec3 MaterialColour;
varying float Diffuse;

varying float sonogramColour;

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main()
{


    vec3 hsb = vec3 (sonogramColour, 1.0, 1.0);
    vec3 rgb = hsv2rgb(hsb);

    vec4 colour = vec4(rgb,1.0);
    gl_FragColor = colour;
}


