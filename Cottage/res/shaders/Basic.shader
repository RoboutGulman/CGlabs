#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colors;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 texCoord;

out vec3 Color;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;

uniform mat4 MVP;
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	FragPos = vec3(u_model * vec4(position, 1.0));
	Normal = normal;
	gl_Position = MVP * vec4(FragPos, 1.0);
	//gl_Position = u_projection * u_view * vec4(FragPos, 1.0f);
	//Color = vec3(1.0);
	Color=colors;
	TexCoord = texCoord;
};

#shader fragment
#version 330 core

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

out vec4 fragColor;

uniform vec3 u_lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform sampler2D u_sampler;

void main()
{
	// ambient
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * u_lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * u_lightColor;

	vec3 result = (ambient + diffuse) * Color;

	//fragColor = vec4(1.0);
	fragColor = texture(u_sampler, TexCoord);
	//fragColor = vec4(ambient + diffuse, 1) * texture2D(u_sampler, TexCoord);
}