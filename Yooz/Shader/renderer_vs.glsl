#version 450 core

// Vertex Attributes
layout (location = 0) in vec2  aPos;
layout (location = 1) in vec2  aTexCoord;
layout (location = 2) in vec4  aColor;
layout (location = 3) in float aTexID;

// View-Projection matrix
uniform mat3x2 uViewProj;

// Interface block
out VS_OUT
{
	vec2  aTexCoord;
	vec4  aColor;
	float aTexID;
} vs_out;

void main()
{
	gl_Position = vec4(uViewProj * vec3(aPos, 1.0), 0.0, 1.0);

	vs_out.aTexCoord = aTexCoord;
	vs_out.aColor    = aColor;
	vs_out.aTexID    = aTexID;
}
