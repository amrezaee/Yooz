#pragma once

#include <yzpch.hpp>

#include <Graphics/yzColor.hpp>
#include <Graphics/yzShader.hpp>
#include <Graphics/yzTexture.hpp>
#include <Math/yzVector2.hpp>

namespace yz
{
struct Vertex
{
	Vec2  position;
	Vec2  texcoord;
	Color color;
	float texid {0.0f};
};

struct BatchData
{
	const Texture& texture;
	Vec2           texcoords[4];
	Color          colors[4];
	Vec2           position;
	Vec2           scale;
	Vec2           origin;
	float          angle;
};

class Batcher
{
public:
	using texture_handle_type = Texture::handle_type;

public:
	void Init(uint32_t max_quads, uint32_t total_texture_units);
	void Destroy();

	// Returns false if it cannot add data.
	// Batch is full, texture units are full, etc.
	bool Add(const BatchData& data);
	void Done();
	void Reset();

	uint32_t GetIndicesCount() const;
	uint32_t GetQuadsCount() const;

	const Texture& GetDefaultTexture() const;

private:
	void InitBuffers();
	void DestroyBuffers();

	void AddQuad(const BatchData& data, const uint32_t texture_index);

private:
	bool m_inited {false};

	Texture m_white_texture;

	// Max texture units target GPU supports. (GPU dependent)
	uint32_t m_total_texture_units {8};
	// Max quads in each batch.
	uint32_t m_max_quads {100};
	uint32_t m_max_vertices {m_max_quads * 4};
	uint32_t m_max_indices {m_max_quads * 6};

	uint32_t m_quad_count {0};

	texture_handle_type* m_texture_units {nullptr};
	uint32_t             m_texture_index {1};  // 0 is white texture

	Vertex* m_vertices {nullptr};
};
}  // namespace yz
