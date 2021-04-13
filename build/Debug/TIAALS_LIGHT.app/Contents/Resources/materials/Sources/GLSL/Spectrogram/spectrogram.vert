

attribute vec4 position;
attribute vec4 normal;
attribute vec2 textureCoordIn;

uniform float shiness;
varying float Diffuse;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

varying float sonogramColour;

void main()
{
    sonogramColour = textureCoordIn.x;
    gl_Position = projectionMatrix * viewMatrix * position;
    
}
