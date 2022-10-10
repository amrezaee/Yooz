#include <Graphics/yzCamera.hpp>


namespace yz
{
Camera::Camera(float l, float r, float t, float b)
        : m_projection(l, r, t, b), m_offset((r - l) * 0.5f, (b - t) * 0.5f)
{
	Calculate();
}

Vec2 Camera::GetPosition() const
{
	return m_position;
}

void Camera::SetPosition(Vec2 position)
{
	if(position == m_position)
		return;
	m_position = position;
	Calculate();
}

float Camera::GetRotation() const
{
	return m_rotation;
}

void Camera::SetRotation(float angle)
{
	if(angle == m_rotation)
		return;
	m_rotation = angle;
	Calculate();
}

float Camera::GetZoom() const
{
	return m_zoom;
}

void Camera::SetZoom(float zoom)
{
	if(zoom == m_zoom)
		return;
	m_zoom = zoom;
	Calculate();
}

Vec2 Camera::GetOffset() const
{
	return m_offset;
}

void Camera::SetOffset(Vec2 offset)
{
	if(offset == m_offset)
		return;
	m_offset = offset;
	Calculate();
}

void Camera::SetProjection(float l, float r, float t, float b)
{
	m_projection.Reset();
	m_projection.Project(l, r, t, b);
	SetOffset({(r - l) * 0.5f, (b - t) * 0.5f});
}

const Transform& Camera::GetView() const
{
	return m_view;
}

const Transform& Camera::GetProjection() const
{
	return m_projection;
}

Transform Camera::GetViewProjection() const
{
	return m_projection * m_view;
}

void Camera::Calculate()
{
	m_view.Reset();
	m_view.Translate(m_offset)
	        .Scale(1.0f / m_zoom)
	        .RotateDegree(-m_rotation)
	        .Translate(-m_position);
}
}  // namespace yz
