#pragma once
#include <vector>
#include <cmath>

namespace Vertex {

	struct Vertex {
		float x, y, z;
		float normal[3];
	};

	std::vector<Vertex> GenerateRectVertex(int x_length, int y_length, int n = 1) {
		int numVertices = pow(n+1, 2);
		std::vector<Vertex> vertices;
		float x_distance = x_length / n; //distance between each vertex on the x-axis
		float y_distance = y_length / n; //distance between each vertex on the y-axis
		for (int x = 0; x <= n; x++) {
			for (int y = 0; y <= n ; y++) {
				Vertex point;
				point.x = y * x_distance;
				point.y = x * y_distance;
				point.z = 0;
				vertices.push_back(point);
			}
		}
		return vertices;

	}

	std::vector<int> CalculateIndices(std::vector<Vertex> vertices, int n) {
		std::vector<int> Indices;
		int size = pow(n, 2);
		
		for (int x = 0; x < size; x++) {
			if (x % n == 0 && !Indices.empty()) {
				Indices.push_back(0 + x + 1);
				Indices.push_back(n + 2 + x);
				Indices.push_back(2 + x);
				Indices.push_back(2 + x);
				Indices.push_back(n + 2 + x);
				Indices.push_back(n + 3 + x);
			}
			else {
				Indices.push_back(0+x);
				Indices.push_back(n + 1 + x);
				Indices.push_back(1 + x);
				Indices.push_back(1 + x);
				Indices.push_back(n + 1 + x);
				Indices.push_back(n + 2 + x);
			}
		}
	}

}
