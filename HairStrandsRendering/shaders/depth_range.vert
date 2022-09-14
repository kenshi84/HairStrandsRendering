#version 330

layout (location=0) in vec3 position;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

out float Depth;

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(position, 1.0f);
    // Depth = gl_Position.z;
    Depth = -(ViewMatrix * ModelMatrix * vec4(position, 1.0f)).z;
    // gl_Position.z += 0.01 / Depth;
}
