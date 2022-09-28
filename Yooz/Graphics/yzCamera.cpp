#include <Graphics/yzCamera.hpp>


namespace yz
{
Camera::Camera() { Calculate(); }

Camera::Camera(const Vec2 origin, const Vec2 position, const float rotation,
               const float zoom):
        m_origin(origin),
        m_position(position), m_rotation(rotation), m_zoom(zoom)
{
	Calculate();
}

void Camera::Update(const Vec2 origin, const Vec2 pos, const float rot,
                    const float zoom)
{
	if((m_position == pos) && (m_rotation == rot) && (m_origin == origin) &&
	   (m_zoom == zoom))
		return;

	m_origin   = origin;
	m_position = pos;
	m_rotation = rot;
	m_zoom     = zoom;
	Calculate();
}

void Camera::SetOrigin(const Vec2 v)
{
	if(v == m_origin) return;
	m_origin = v;
	Calculate();
}

void Camera::SetPosition(const Vec2 pos)
{
	if(pos == m_position) return;
	m_position = pos;
	Calculate();
}

void Camera::SetRotation(const float angle)
{
	if(angle == m_rotation) return;
	m_rotation = angle;
	Calculate();
}

void Camera::SetZoom(const float zoom)
{
	if(zoom == m_zoom) return;
	m_zoom = zoom;
	Calculate();
}

Vec2 Camera::GetOrigin() const { return m_origin; }

Vec2 Camera::GetPosition() const { return m_position; }

float Camera::GetRotation() const { return m_rotation; }

float Camera::GetZoom() const { return m_zoom; }

const Transform& Camera::GetTransform() const { return m_view; }

void Camera::Calculate()
{
	m_view.Translate(-m_position.x, -m_position.y)
	        .Scale(m_zoom)
	        .RotateDegree(m_rotation)
	        .Translate(m_origin);
}
}  // namespace yz
