#pragma once

#include <Core/yzBase.hpp>
#include <Core/yzWindow.hpp>
#include <Graphics/yzColor.hpp>
#include <Graphics/yzGraphicsFeatures.hpp>
#include <Graphics/yzGraphicsParams.hpp>
#include <Graphics/yzGraphicsStates.hpp>
#include <Graphics/yzRasterizer.hpp>

namespace yz
{
class GraphicsDevice
{
public:
	GraphicsDevice();

	void Init(GraphicsParams& params, Window& window);
	void Destroy();

	void SetClearColor(Color color);
	void ClearBuffers() const;
	void SwapBuffers() const;

	void UpdateViewport(Vec2u size);

	void ApplyChanges();

	Handle                  GetHandle() const;
	GraphicsAPI             GetAPI() const;
	GraphicsParams&         GetParams();
	const GraphicsFeatures& GetFeatures() const;
	Rasterizer&             GetRasterizer();

private:
	void SetupParams();
	bool CheckParams();

private:
	bool m_inited {false};

	Handle            m_handle {nullptr};
	const GraphicsAPI m_api;
	GraphicsFeatures  m_features;
	GraphicsParams    m_params;
	Color             m_clear_color;
	Rasterizer        m_rasterizer;
};
}  // namespace yz
