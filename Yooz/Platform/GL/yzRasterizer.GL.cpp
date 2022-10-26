#include <Graphics/yzRasterizer.hpp>

#include <yzpch.hpp>

namespace yz
{
void Rasterizer::SetFillMode(FillMode fm)
{
	if(fm == m_fill_mode)
		return;

	glPolygonMode(GL_FRONT_AND_BACK, fm == FillMode::Fill ? GL_FILL : GL_LINE);
	m_fill_mode = fm;
}

void Rasterizer::ToggleFillMode()
{
	if(m_fill_mode == FillMode::Fill)
		SetFillMode(FillMode::Line);
	else
		SetFillMode(FillMode::Fill);
}

FillMode Rasterizer::GetFillMode() const
{
	return m_fill_mode;
}
}  // namespace yz
