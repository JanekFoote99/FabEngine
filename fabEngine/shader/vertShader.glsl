#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform float timer;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 UV;
out vec3 normal;
out vec3 fragPos;

void main(){

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1.0);

    fragPos = (modelMatrix * vec4(inPosition, 1.0)).xyz;
    normal = vertexNormal;
    UV = vertexUV;
}

