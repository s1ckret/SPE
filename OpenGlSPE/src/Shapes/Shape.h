#pragma once
#include "Physics\Material.h"

#include "Graphics\VertexArray.h"
#include "Graphics\VertexBuffer.h"
#include "Graphics\VertexBufferLayout.h"

enum ShapeType
{
	CircleType = 0,
	PolyType
};

struct Vertex
{
	union {
		struct {
			float x, y;
			float r, g, b;
		};
		struct {
			glm::fvec2 position;
			glm::fvec3 color;
		};
	};
	Vertex(float _x, float _y, float _r, float _g, float _b) :
		x(_x),
		y(_y),
		r(_r),
		g(_g),
		b(_b)
	{}

	Vertex(glm::fvec2 pos, glm::fvec3 col) :
		position(pos),
		color(col)
	{}
	Vertex() :
		x(0.f),
		y(0.f),
		r(0.f),
		g(0.f),
		b(0.f)
	{}
};

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual Shape* Clone() = 0;

	void SetMaterial(Material_Table mt = Material_Table::Static, bool connectivity = 1);

	void SetVerticies(Vertex* verticies, unsigned int count);
	void SetVerticiesPositions(float* positions, unsigned int count);
	void SetVerticiesPositions(glm::vec2* positions, unsigned int count);
	void SetVerticiesColors(float* colors, unsigned int count);

	void Translate(float x, float y);
	void Translate(glm::vec2 tr);
	void SetTranslation(float x, float y);
	void SetTranslation(glm::vec2 tr);

	void Rotate(float d_rad);
	void SetRotation(float rad);

	const Material & GetMaterial() const;
	const ShaderBundle & GetShaderBundle() const;

	const glm::vec2 GetPosition() const;
	const float GetOrientation() const;

	const unsigned int GetVerticiesCount() const;
	const Vertex * GetVerticies() const;
	const Vertex GetVertex(const unsigned int index) const;
		
	const glm::mat4 & GetRotationMat() const;
	const glm::mat4 & GetTranslationMat() const;
	const glm::vec2 & GetTranslationVec() const;

	virtual const unsigned int GetType() const = 0;

	virtual void Draw(Renderer& renderer);
protected:
	virtual void InitBuffers();

protected:
	std::vector<Vertex> m_verticies;
	glm::mat4 m_translation_mat;
	glm::mat4 m_rotation_mat;

	glm::vec2 m_translation;
	float m_orientation;

	unsigned int m_verticies_count;

	VertexBuffer m_vertex_buffer;
	VertexArray m_vertex_array;
	VertexBufferLayout m_vertex_layout;
	ShaderBundle m_shader_bundle;
	Material m_material;
};