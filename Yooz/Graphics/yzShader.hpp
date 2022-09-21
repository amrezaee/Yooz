#pragma once

#include <Math/yzTransform.hpp>
#include <Math/yzVector2.hpp>

#include <yzStds.hpp>


namespace yz
{
class Shader
{
public:
	Shader(const std::string& vsrc, const std::string& fsrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetFloat(const std::string& name, const float f) const;
	void SetVec2(const std::string& name, const Vec2 v) const;

	void SetInt(const std::string& name, const int i) const;
	void SetVec2i(const std::string& name, const Vec2i v) const;

	void SetUInt(const std::string& name, const unsigned int i) const;
	void SetVec2u(const std::string& name, const Vec2u v) const;

	void SetTransform(const std::string& name, const Transform& t) const;

private:
	struct Pimpl;
	std::unique_ptr<Pimpl> m_impl;
};
}  // namespace yz
