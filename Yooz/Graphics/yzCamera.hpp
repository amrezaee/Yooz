#pragma once

#include <Math/yzTransform.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
class Camera
{
public:
	Camera();
	Camera(const Vec2 origin, const Vec2 position, const float rotation,
	       const float zoom);

	void SetOrigin(const Vec2 v);
	void SetPosition(const Vec2 pos);
	void SetRotation(const float angle);
	void SetZoom(const float zoom);

	Vec2  GetOrigin() const;
	Vec2  GetPosition() const;
	float GetRotation() const;
	float GetZoom() const;

	const Transform& GetTransform() const;

private:
	void Calculate();

private:
	Transform m_view;
	Vec2      m_position {0.0f, 0.0f};
	Vec2      m_origin {0.0f, 0.0f};
	float     m_rotation {0.0f};
	float     m_zoom {1.0f};
};
}  // namespace yz
