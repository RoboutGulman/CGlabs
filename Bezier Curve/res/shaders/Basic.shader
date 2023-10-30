#shader vertex
#version 330 core
layout(location = 0) in vec2 position;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

void main()
{
	gl_Position = m_projection * m_view * m_model * vec4(position, 0.0, 1.0);
}

#shader fragment
#version 330 core

in vec2 texCoords;

out vec4 color;

uniform vec4 u_color;

void main()
{
	color = u_color;
}