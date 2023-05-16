#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 vertexColor;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position, 1.0);
	vertexColor = color;
};

#shader fragment
#version 330 core

in vec4 vertexColor;

out vec4 color;

void main()
{
	color = vertexColor;
};