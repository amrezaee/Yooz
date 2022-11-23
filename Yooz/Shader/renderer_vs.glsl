#version 450 core

// Vertex Attributes
layout (location = 0) in vec2  aPos;
layout (location = 1) in vec2  aTexCoord;
layout (location = 2) in vec4  aColor;
layout (location = 3) in float aTexID;

// View-Projection matrix
uniform mat3x2 uViewProj;

struct VertexOutput
{
	vec2  texCoord;
	vec4  color;
	float texID;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.color = aColor;
	Output.texCoord = aTexCoord;
	Output.texID = aTexID;

	gl_Position = vec4(uViewProj * vec3(aPos, 1.0f), 0.0f, 1.0f);
}
