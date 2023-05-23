#shader vertex
#version 330

layout(location = 0) in vec2 position;

flat out vec3 startPos;
out vec3 vertPos;

uniform mat4 m_model;
uniform mat4 m_view;
uniform mat4 m_projection;

void main()
{
	vec4 pos = m_projection * m_view * m_model * vec4(position, 0.0, 1.0);
	gl_Position = pos;
	vertPos = pos.xyz / pos.w;
	startPos = vertPos;
}

#shader fragment
#version 330

flat in vec3 startPos;
in vec3 vertPos;

out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_dashSize;
uniform float u_gapSize;

void main()
{
	vec2 dir = (vertPos.xy - startPos.xy) * u_resolution / 2.0;
	float dist = length(dir);

	if (fract(dist / (u_dashSize + u_gapSize)) > u_dashSize / (u_dashSize + u_gapSize))
		discard;
	fragColor = vec4(1.0);
}