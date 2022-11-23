#version 450 core

layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D uTextures[32];

struct VertexOutput
{
	vec2  texCoord;
	vec4  color;
	float texID;
};

layout (location = 0) in VertexOutput Input;

void main()
{
	switch(int(Input.texID))
	{
	case 0: outColor =  Input.color * texture(uTextures[0],  Input.texCoord); break;
	case 1: outColor =  Input.color * texture(uTextures[1],  Input.texCoord); break;
	case 2: outColor =  Input.color * texture(uTextures[2],  Input.texCoord); break;
	case 3: outColor =  Input.color * texture(uTextures[3],  Input.texCoord); break;
	case 4: outColor =  Input.color * texture(uTextures[4],  Input.texCoord); break;
	case 5: outColor =  Input.color * texture(uTextures[5],  Input.texCoord); break;
	case 6: outColor =  Input.color * texture(uTextures[6],  Input.texCoord); break;
	case 7: outColor =  Input.color * texture(uTextures[7],  Input.texCoord); break;
	case 8: outColor =  Input.color * texture(uTextures[8],  Input.texCoord); break;
	case 9: outColor =  Input.color * texture(uTextures[9],  Input.texCoord); break;
	case 10: outColor = Input.color * texture(uTextures[10], Input.texCoord); break;
	case 11: outColor = Input.color * texture(uTextures[11], Input.texCoord); break;
	case 12: outColor = Input.color * texture(uTextures[12], Input.texCoord); break;
	case 13: outColor = Input.color * texture(uTextures[13], Input.texCoord); break;
	case 14: outColor = Input.color * texture(uTextures[14], Input.texCoord); break;
	case 15: outColor = Input.color * texture(uTextures[15], Input.texCoord); break;
	case 16: outColor = Input.color * texture(uTextures[16], Input.texCoord); break;
	case 17: outColor = Input.color * texture(uTextures[17], Input.texCoord); break;
	case 18: outColor = Input.color * texture(uTextures[18], Input.texCoord); break;
	case 19: outColor = Input.color * texture(uTextures[19], Input.texCoord); break;
	case 20: outColor = Input.color * texture(uTextures[20], Input.texCoord); break;
	case 21: outColor = Input.color * texture(uTextures[21], Input.texCoord); break;
	case 22: outColor = Input.color * texture(uTextures[22], Input.texCoord); break;
	case 23: outColor = Input.color * texture(uTextures[23], Input.texCoord); break;
	case 24: outColor = Input.color * texture(uTextures[24], Input.texCoord); break;
	case 25: outColor = Input.color * texture(uTextures[25], Input.texCoord); break;
	case 26: outColor = Input.color * texture(uTextures[26], Input.texCoord); break;
	case 27: outColor = Input.color * texture(uTextures[27], Input.texCoord); break;
	case 28: outColor = Input.color * texture(uTextures[28], Input.texCoord); break;
	case 29: outColor = Input.color * texture(uTextures[29], Input.texCoord); break;
	case 30: outColor = Input.color * texture(uTextures[30], Input.texCoord); break;
	case 31: outColor = Input.color * texture(uTextures[31], Input.texCoord); break;
	}
}
