#version 450

layout (location = 0) out vec3;

void main () {
	const vec3 positions[3] = vec3[3] (
		vec3(1.f, 1.f, 0.f),
		vec3(-1.f, 1.f, 0.f),
		vec3(0.f, -1.f, 0.f)
	);

	// ouput the position of each vertex
	gl_Position = vec4(positions[gl_VertexIndex], 1.0f);
}