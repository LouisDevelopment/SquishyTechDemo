#version 330 core
out vec4 FragColor;

in vec2 texCoord;
in vec4 ourColor;

uniform sampler2D image;

void main()
{
    FragColor = ourColor * texture(image, texCoord);
}