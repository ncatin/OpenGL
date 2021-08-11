#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include "glm/glm.hpp"
#include "glm/gtc/random.hpp"

namespace Vertex {

	struct Vertex {
		float x, y, z;
		float v_normal[3];
	};


	std::vector<Vertex> GenerateRectVertex(float x_length = 5, float y_length = 5, float n = 4);

	std::vector<unsigned int> CalculateIndices(std::vector<Vertex> vertices, int n = 4);

	void CalculateNormals(std::vector<Vertex>& vertex, const std::vector<unsigned int>& indices, float n = 4);

	std::vector<Vertex> GenerateTorusVertex(int radius);

	std::vector<unsigned int> CalculateTorusIndices(std::vector<Vertex> vertices, int n = 12);

}

