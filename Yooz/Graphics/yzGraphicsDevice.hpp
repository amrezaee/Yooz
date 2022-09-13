#pragma once

#include <Core/yzBase.hpp>
#include <Graphics/yzColor.hpp>
#include <Graphics/yzGraphicsStates.hpp>
#include <Graphics/yzGraphicsFeatures.hpp>

namespace yz
{
class Application;

class GraphicsDevice
{
public:
	GraphicsDevice(Application& app);

	// must be called before Init
	void BeforeInit();
	void Init();
	void BeforeUpdate();
	void Update();
	void Destroy();

	void SetColorBufferColor(Color color);

	GraphicsAPI GetAPI() const;
	Handle      GetHandle() const;

private:
	GraphicsFeatures  m_features;
	Color             m_color_buffer_color;
	bool              m_inited {false};
	Application&      m_app;
	const GraphicsAPI m_api;
	Handle            m_handle {nullptr};
};
}  // namespace yz
