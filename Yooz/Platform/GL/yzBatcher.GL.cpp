#include <Graphics/yzBatcher.hpp>

#include <yzpch.hpp>

#include <Core/yzAssert.hpp>
#include <Math/yzTransform.hpp>

namespace yz
{
static struct
{
	GLuint vbo {0};
	GLuint ibo {0};
	GLuint vao {0};
} g_data;

void Batcher::Init(uint32_t max_quads, uint32_t total_texture_units)
{
	YZ_ASSERT(!m_inited);

	m_total_texture_units = total_texture_units;
	m_max_quads           = max_quads;
	m_max_vertices        = max_quads * 4;
	m_max_indices         = max_quads * 6;

	m_texture_units = new texture_handle_type[m_total_texture_units]();
	m_vertices      = new Vertex[m_max_vertices]();

	InitBuffers();

	uint32_t c = Color::WHITE.GetPacked();
	m_white_texture.Create({1, 1}, TextureFilter::Linear, TextureWrapMode::Repeat,
	                       reinterpret_cast<uint8_t*>(&c));
	m_texture_units[0] = m_white_texture.GetHandle();

	m_inited = true;
}

void Batcher::Destroy()
{
	YZ_ASSERT(m_inited);

	DestroyBuffers();

	delete[] m_texture_units;
	delete[] m_vertices;

	m_texture_units = nullptr;
	m_vertices      = nullptr;

	m_white_texture.Destroy();

	Reset();

	m_inited = false;
}

bool Batcher::Add(const BatchData& data)
{
	if(m_quad_count >= m_max_quads)
		return false;

	for(unsigned int i = 0; i < (m_total_texture_units - 1); ++i)
	{
		if(data.texture.GetHandle() == m_texture_units[i])
		{
			AddQuad(data, i);
			return true;
		}
	}

	if(m_texture_index > (m_total_texture_units - 1))
		return false;

	m_texture_units[m_texture_index++] = data.texture.GetHandle();
	AddQuad(data, m_texture_index);
	return true;
}

void Batcher::Done()
{
	if(m_quad_count == 0)
		return;

	glNamedBufferSubData(g_data.vbo, 0, (m_quad_count * sizeof(Vertex)) << 2,
	                     m_vertices);

	for(unsigned int i = 0; i < m_texture_index; ++i)
	{
		glBindTextureUnit(i, m_texture_units[i]);
	}

	glBindVertexArray(g_data.vao);
}

void Batcher::Reset()
{
	m_texture_index = 1;
	m_quad_count    = 0;
}

uint32_t Batcher::GetIndicesCount() const
{
	return m_quad_count * 6u;
}

uint32_t Batcher::GetQuadsCount() const
{
	return m_quad_count;
}

const Texture& Batcher::GetDefaultTexture() const
{
	return m_white_texture;
}

void Batcher::AddQuad(const BatchData& data, const uint32_t texture_index)
{
	Transform model;

	Vec2 size = data.texture.GetSize();
	size *= data.scale;

	model.Translate(data.position)
	        .RotateDegree(data.angle)
	        .Translate(-0.5f * size.x, -0.5f * size.y)
	        .Scale(size);

	// Origin offsets.
	Vec2 oov1(-data.origin);
	Vec2 oov2(1.0f - data.origin.x, -data.origin.y);
	Vec2 oov3(1.0f - data.origin.x, 1.0f - data.origin.y);
	Vec2 oov4(-data.origin.x, 1.0f - data.origin.y);

	uint32_t vc = m_quad_count * 4;

	// Vertex 1
	model.TransformVec2(oov1, m_vertices[vc].position);
	m_vertices[vc].texcoord = data.texcoords[0];
	m_vertices[vc].color    = data.colors[0];
	m_vertices[vc++].texid  = static_cast<float>(texture_index);

	// Vertex 2
	model.TransformVec2(oov2, m_vertices[vc].position);
	m_vertices[vc].texcoord = data.texcoords[1];
	m_vertices[vc].color    = data.colors[1];
	m_vertices[vc++].texid  = static_cast<float>(texture_index);

	// Vertex 3
	model.TransformVec2(oov3, m_vertices[vc].position);
	m_vertices[vc].texcoord = data.texcoords[2];
	m_vertices[vc].color    = data.colors[2];
	m_vertices[vc++].texid  = static_cast<float>(texture_index);

	// Vertex 4
	model.TransformVec2(oov4, m_vertices[vc].position);
	m_vertices[vc].texcoord = data.texcoords[3];
	m_vertices[vc].color    = data.colors[3];
	m_vertices[vc].texid    = static_cast<float>(texture_index);

	++m_quad_count;
}

void Batcher::InitBuffers()
{
	// Clear g_data.
	std::memset(&g_data, 0, sizeof(g_data));

	{
		uint32_t* indices = new uint32_t[m_max_indices];

		// Fill index buffer.
		// Its content is known and constant.
		for(unsigned int offset = 0, i = 0; i < m_max_indices; i += 6, offset += 4)
		{
			indices[i]     = offset;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset;
		}
		// Create Index Buffer Object and fill memory
		// Actually we make 2 buffers 1 for vbo and 1 for ibo in one call.
		// :)
		glCreateBuffers(2, &g_data.vbo);
		glNamedBufferStorage(g_data.ibo, sizeof(indices[0]) * m_max_indices, indices,
		                     GL_DYNAMIC_STORAGE_BIT);
		// We uploaded indices to VRAM and now we can delete it from RAM.
		delete[] indices;
	}

	// Create Vertex Buffer Object and allocate memory.
	glNamedBufferStorage(g_data.vbo, sizeof(m_vertices[0]) * m_max_vertices, nullptr,
	                     GL_DYNAMIC_STORAGE_BIT);

	// Create Vertex Array Object.
	glCreateVertexArrays(1, &g_data.vao);

	// Bind buffers.
	glVertexArrayVertexBuffer(g_data.vao, 0, g_data.vbo, 0, sizeof(Vertex));
	glVertexArrayElementBuffer(g_data.vao, g_data.ibo);

	// Define attributes.
	glEnableVertexArrayAttrib(g_data.vao, 0);  // Position
	glEnableVertexArrayAttrib(g_data.vao, 1);  // Texture Coordinate
	glEnableVertexArrayAttrib(g_data.vao, 2);  // Color
	glEnableVertexArrayAttrib(g_data.vao, 3);  // Texture Index

	glVertexArrayAttribFormat(g_data.vao, 0, 2, GL_FLOAT, GL_FALSE,
	                          offsetof(Vertex, position));

	glVertexArrayAttribFormat(g_data.vao, 1, 2, GL_FLOAT, GL_FALSE,
	                          offsetof(Vertex, texcoord));

	glVertexArrayAttribFormat(g_data.vao, 2, 4, GL_UNSIGNED_BYTE, GL_TRUE,
	                          offsetof(Vertex, color));

	glVertexArrayAttribFormat(g_data.vao, 3, 1, GL_FLOAT, GL_FALSE,
	                          offsetof(Vertex, texid));

	glVertexArrayAttribBinding(g_data.vao, 0, 0);
	glVertexArrayAttribBinding(g_data.vao, 1, 0);
	glVertexArrayAttribBinding(g_data.vao, 2, 0);
	glVertexArrayAttribBinding(g_data.vao, 3, 0);
}

void Batcher::DestroyBuffers()
{
	glDeleteBuffers(2, &g_data.vbo);
	glDeleteVertexArrays(1, &g_data.vao);
}
}  // namespace yz
