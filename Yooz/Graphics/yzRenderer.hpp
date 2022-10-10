#pragma once

#include <Graphics/yzBatcher.hpp>
#include <Graphics/yzCamera.hpp>
#include <Graphics/yzGraphicsDevice.hpp>
#include <Graphics/yzShader.hpp>
#include <Graphics/yzTexture.hpp>
#include <Math/yzVector2.hpp>

#include <yzSTD.hpp>

namespace yz
{
struct RenderStats
{
	std::uint32_t total_draw_calls {0};
	std::uint32_t draw_calls {0};

	std::uint32_t total_quads {0};
	std::uint32_t quads {0};
};

class Renderer
{
public:
	Renderer(GraphicsDevice& gd);

	void Init();
	void Destroy();

	void Begin();
	void Begin(const Camera& camera);
	void End();

	const RenderStats& GetStats() const;

	void OnResize(Vec2u size);

	void DrawQuad(const Texture& texture, Color color, Vec2 pos, Vec2 scale,
	              float angle, Vec2 origin);

	void DrawQuad(const Texture& texture, Color color, Vec2 pos, Vec2 scale,
	              float angle);

	void DrawQuad(const Texture& texture, Vec2 pos);

	void DrawQuad(Color color, Vec2 pos, Vec2 scale, float angle, Vec2 origin);

	void DrawQuad(Color color, Vec2 pos, Vec2 scale, float angle);

	void DrawQuad(Color color, Vec2 pos);

private:
	bool m_begin {false};

	GraphicsDevice& m_gd;

	Shader m_shader;

	Camera m_camera;

	Batcher m_batcher;

	RenderStats m_stats;
};
}  // namespace yz
