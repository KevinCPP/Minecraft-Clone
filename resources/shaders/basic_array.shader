#shader vertex
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aTexCoord;

out vec3 vTexCoord;

uniform mat4 uMVPMatrix;

void main()
{
    gl_Position = uMVPMatrix * vec4(aPosition, 1.0);
    vTexCoord = aTexCoord;
}

#shader fragment
#version 330 core

in vec3 vTexCoord;
out vec4 fragColor;

uniform sampler2DArray uTexture;

void main()
{
    fragColor = texture(uTexture, vTexCoord);
}
