#pragma once

#include "Shape.h"

class Circle : public Shape
{
public:
	Circle();
	Circle(float r, unsigned int verticies_count);
	~Circle();
	Shape* Clone() override;

	void SetVerticies(Vertex* verticies, unsigned int count) = delete;
	void SetVerticiesPositions(float* positions, unsigned int count) = delete;
	void SetVerticiesColors(float* colors, unsigned int count) = delete;

	void SetRadius(float r, unsigned int verticies_count);
	float GetRadius() const;

	const unsigned int GetType() const override;
private:
	void GenVerticiesPositions();

private:
	float m_radius;
};