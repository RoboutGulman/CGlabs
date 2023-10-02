#shader vertex
#version 330 core

layout(location = 0) in vec2 position;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	gl_Position =  u_projection * u_view * u_model * vec4(position, 0.0, 1.0);
};

#shader fragment
#version 330 core

out vec4 fragColor;

uniform vec2 resolution;
uniform sampler1D tex;
uniform float zoom;
uniform vec2 controls;

const float MAX_ITER = 128.0;

float mandelbrot(vec2 uv)
{
	vec2 c = 4.0 * uv - vec2(0.7, 0.0);
	c = c * 1.0;
	vec2 z = vec2(0.0);
	float iter = 0.0;
	for (float i; i < MAX_ITER; i++)
	{
		z = vec2(z.x * z.x - z.y * z.y,
				2.0 * z.x * z.y) + c;
		if (dot(z, z) > 4.0)
			return iter / MAX_ITER;
		iter++;
	}
	return 0.0;
}

vec2 getCoordinatesFromScreen(vec2 fragCoord, vec2 vSystemResolution, vec4 coordinateRange)
{
	vec2 normalizedCoordinates = gl_FragCoord.xy / vSystemResolution.xy; // From 0 to 1 where pixel is in screen

	float horizontalSize = coordinateRange.y - coordinateRange.x; 
	float verticalSize = coordinateRange.w - coordinateRange.z; 

	normalizedCoordinates.x = normalizedCoordinates.x * horizontalSize + coordinateRange.x; // Multiply by size and add initial offset position
	normalizedCoordinates.y = normalizedCoordinates.y * verticalSize + coordinateRange.z;

	return normalizedCoordinates;
}

void main()
{
	vec2 uv = getCoordinatesFromScreen(gl_FragCoord.xy,
		resolution.xy, vec4(-1.0, 1.0, -1.0, 1.0) * zoom + vec4(vec2(-controls.x), vec2(controls.y)));

	float m = mandelbrot(uv);

	m = pow(m, 0.45);
	//fragColor = vec4(col, 1.0);
	fragColor = texture1D(tex, m);
};