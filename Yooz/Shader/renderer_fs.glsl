#version 450 core

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D uTextures[32];

in VS_OUT
{
	vec2  aTexCoord;
	vec4  aColor;
	float aTexID;
} fs_in;

void main()
{
	outColor = fs_in.aColor * texture(uTextures[int(fs_in.aTexID)], fs_in.aTexCoord);
}
