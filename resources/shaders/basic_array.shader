#shader vertex
#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aTexCoord;

out vec3 vTexCoord;

uniform mat4 uModelMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;
uniform float uScaleFactor;

void main()
{
    mat4 mvp = uProjectionMatrix * uViewMatrix * uModelMatrix;
    gl_Position = mvp * vec4(aPosition, uScaleFactor);
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
