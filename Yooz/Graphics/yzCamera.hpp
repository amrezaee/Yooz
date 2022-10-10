#pragma once

#include <Math/yzTransform.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
class Camera
{
public:
	Camera() = default;
	Camera(float l, float r, float t, float b);

	Vec2 GetPosition() const;
	void SetPosition(Vec2 pos);

	float GetRotation() const;
	void  SetRotation(float angle);

	float GetZoom() const;
	void  SetZoom(float zoom);

	Vec2 GetOffset() const;
	void SetOffset(Vec2 offset);

	void SetProjection(float l, float r, float t, float b);

	const Transform& GetView() const;
	const Transform& GetProjection() const;
	Transform        GetViewProjection() const;

private:
	void Calculate();

private:
	Transform m_view;
	Transform m_projection;

	Vec2  m_offset;
	Vec2  m_position;
	float m_rotation {0.0f};
	float m_zoom {1.0f};
};
}  // namespace yz
