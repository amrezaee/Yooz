#pragma once

#include <Graphics/yzGraphicsStates.hpp>

namespace yz
{
class Rasterizer
{
public:
	Rasterizer() = default;

	void     SetFillMode(FillMode fm);
	void     ToggleFillMode();
	FillMode GetFillMode() const;

private:
	FillMode m_fill_mode {FillMode::Fill};
};
}  // namespace yz
