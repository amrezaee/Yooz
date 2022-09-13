#pragma once

#include <Core/yzWindow.hpp>
#include <Math/yzRectangle.hpp>

#include <yzStds.hpp>

namespace yz
{
class Application
{
public:
	Application(const std::string& name, std::uint32_t width,
	            std::uint32_t height);

	void Execute();
	void Close();
	void Kill();

	rectu GetBounds() const;

	const std::string GetName() const;

private:
	void Init();
	void Update();
	void Exit();

private:
	Window      m_window;
	rectu       m_bounds;
	std::string m_name;
	// bool   m_allow_alt_f4 {true};
	bool m_inited {false};
	bool m_running {true};
	bool m_suspended {false};
};
}  // namespace yz
