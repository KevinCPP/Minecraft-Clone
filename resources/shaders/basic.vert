#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 vTexCoord;

uniform mat4 uMVPMatrix;

void main()
{
    gl_Position = uMVPMatrix * vec4(aPosition, 1.0);
    vTexCoord = aTexCoord;
}


