#include <Graphics/yzShader.hpp>

#include <yzDeps.hpp>

namespace yz
{
struct GLShaderData
{
	GLuint vertex_shader {0};
	GLuint fragment_shader {0};
	GLuint program {0};
};

static GLShaderData data;

Shader::Shader(const std::string& vsrc, const std::string& fsrc)
{
	data.vertex_shader   = glCreateShader(GL_VERTEX_SHADER);
	data.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	data.program         = glCreateProgram();

	const char* vsrc_ptr = vsrc.c_str();
	const char* fsrc_ptr = fsrc.c_str();
	glShaderSource(data.vertex_shader, 1, &vsrc_ptr, nullptr);
	glCompileShader(data.vertex_shader);

	glShaderSource(data.fragment_shader, 1, &fsrc_ptr, nullptr);
	glCompileShader(data.fragment_shader);

	glAttachShader(data.program, data.vertex_shader);
	glAttachShader(data.program, data.fragment_shader);
	glLinkProgram(data.program);

	glDeleteShader(data.vertex_shader);
	glDeleteShader(data.fragment_shader);
}

Shader::~Shader() { glDeleteProgram(data.program); }

void Shader::Bind() const { glUseProgram(data.program); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetFloat(const std::string& name, const float f) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform1f(loc, f);
}

void Shader::SetVec2(const std::string& name, const Vec2 v) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform2f(loc, v.x, v.y);
}

void Shader::SetInt(const std::string& name, const int i) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform1i(loc, i);
}

void Shader::SetVec2i(const std::string& name, const Vec2i v) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform2i(loc, v.x, v.y);
}

void Shader::SetUInt(const std::string& name, const unsigned int i) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform1ui(loc, i);
}

void Shader::SetVec2u(const std::string& name, const Vec2u v) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform2ui(loc, v.x, v.y);
}

void Shader::SetTransform(const std::string& name, const Transform& t) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniformMatrix3x2fv(loc, 1, GL_TRUE, t.GetPtr());
}

void Shader::SetColor(const std::string& name, const Color color) const
{
	GLuint loc = glGetUniformLocation(data.program, name.c_str());
	glUniform4f(loc, color.GetRed(), color.GetGreen(), color.GetBlue(),
	            color.GetAlpha());
}
}  // namespace yz
