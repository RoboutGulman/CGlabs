#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec3 FragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	FragPos = (u_model * vec4(position, 1.0)).xyz;
	gl_Position = u_projection * u_view * vec4(FragPos, 1.0f);
};

#shader fragment
#version 330 core

in vec3 FragPos;

out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_radius;
uniform float u_thickness;

float circle(in vec2 st, in float radius, in vec2 centerOffset)
{
	vec2 dist = st - (vec2(0.5) - centerOffset);
	float aspectRatio = u_resolution.x / u_resolution.y;
	dist = vec2(aspectRatio * dist.x, dist.y);
	return 1. - smoothstep(radius - (radius * 0.1), radius + (radius * 0.1), dot(dist, dist) * 4.0);
}

void main()
{
	vec2 st = gl_FragCoord.xy / u_resolution.xy;

	vec2 firstRingOffset = vec2(0.0f, 0.0f);
	float inInnerCircle = circle(st, u_radius / u_resolution.x, firstRingOffset);
	float inOuterCircle = circle(st, (1 + u_thickness) * u_radius / u_resolution.x, firstRingOffset);

	if (inInnerCircle != 0.0f && inOuterCircle != 0.0f)
	{
		fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (inInnerCircle == 0.0f && inOuterCircle != 0.0f)
	{
		fragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else
	{
		fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}