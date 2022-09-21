#include <Graphics/yzShader.hpp>

#include <yzDeps.hpp>

namespace yz
{
struct Shader::Pimpl
{
	GLuint program {0};
};

Shader::Shader(const std::string& vsrc, const std::string& fsrc):
        m_impl(std::make_unique<Pimpl>())
{
	GLuint vid      = glCreateShader(GL_VERTEX_SHADER);
	GLuint fid      = glCreateShader(GL_FRAGMENT_SHADER);
	m_impl->program = glCreateProgram();

	const char* vsrc_ptr = vsrc.c_str();
	const char* fsrc_ptr = fsrc.c_str();
	glShaderSource(vid, 1, &vsrc_ptr, nullptr);
	glCompileShader(vid);

	glShaderSource(fid, 1, &fsrc_ptr, nullptr);
	glCompileShader(fid);

	glAttachShader(m_impl->program, vid);
	glAttachShader(m_impl->program, fid);
	glLinkProgram(m_impl->program);

	glDeleteShader(vid);
	glDeleteShader(fid);
}

Shader::~Shader() { glDeleteProgram(m_impl->program); }

void Shader::Bind() const { glUseProgram(m_impl->program); }
void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetFloat(const std::string& name, const float f) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniform1f(loc, f);
}

void Shader::SetVec2(const std::string& name, const Vec2 v) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniform2f(loc, v.x, v.y);
}

void Shader::SetInt(const std::string& name, const int i) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniform1i(loc, i);
}

void Shader::SetVec2i(const std::string& name, const Vec2i v) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniform2i(loc, v.x, v.y);
}

void Shader::SetUInt(const std::string& name, const unsigned int i) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniform1ui(loc, i);
}

void Shader::SetVec2u(const std::string& name, const Vec2u v) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniform2ui(loc, v.x, v.y);
}

void Shader::SetTransform(const std::string& name, const Transform& t) const
{
	GLuint loc = glGetUniformLocation(m_impl->program, name.c_str());
	glUniformMatrix3x2fv(loc, 1, GL_TRUE, t.GetPtr());
}

}  // namespace yz
