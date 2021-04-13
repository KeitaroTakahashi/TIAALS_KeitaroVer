uniform vec4 materialColour;
uniform vec4 diffuseColour;
varying float Diffuse;

varying float lightIntensity;

void main()
{
    float l = max (0.3, lightIntensity * 0.3);
    float l2 = max(0.3, lightIntensity * 0.3);
    /* vec4 colour = vec4 (l, 0.1, 0.3, 1.0) + vec4(0.0, l2, 0.2, 1.0); */
    vec4 colour = vec4(materialColour.xyz * l, materialColour.w) + vec4(diffuseColour.xyz * l2, diffuseColour.w);


    gl_FragColor = colour;
}
