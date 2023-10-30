#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	float theta = position.x;
	float R = (1.0 + sin(theta)) * (1.0 + 0.9 * cos(8.0 * theta)) * (1.0 + 0.1 * cos(24.0 * theta)) * (0.5 + 0.05 * cos(140.0 * theta));
	float x = R * cos(theta) * 0.5;
	float y = R * sin(theta) * 0.5;
	
	gl_Position = u_projection * u_view * u_model * vec4(x, y, 1.0, 1.0);
}

#shader fragment
#version 330 core

out vec4 color;

void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
};