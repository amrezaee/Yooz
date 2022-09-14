#pragma once

#include <Core/yzBase.hpp>
#include <Graphics/yzColor.hpp>
#include <Graphics/yzGraphicsFeatures.hpp>
#include <Graphics/yzGraphicsParams.hpp>
#include <Graphics/yzGraphicsStates.hpp>

namespace yz
{
class Application;

class GraphicsDevice
{
public:
	GraphicsDevice(GraphicsParams& params);

	// must be called before Init
	void BeforeInit();
	void Init();
	void BeforeUpdate();
	void Update();
	void Destroy();

	void SetColorBufferColor(Color color);

	GraphicsAPI     GetAPI() const;
	Handle          GetHandle() const;
	GraphicsParams& GetParams();

private:
	bool              m_inited {false};
	const GraphicsAPI m_api;
	GraphicsFeatures  m_features;
	GraphicsParams    m_params;
	Color             m_color_buffer_color;
	Handle            m_handle {nullptr};
};
}  // namespace yz
