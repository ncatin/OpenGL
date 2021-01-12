#pragma once
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

	std::vector<Vertex> GenerateRectVertex(float x_length = 5, float y_length = 5, float n = 4) {
		std::cout << "Generating Vertexes " << std::endl;
		int numVertices = pow(n+1, 2);
		std::vector<Vertex> vertices;
		float x_distance = x_length / n; //distance between each vertex on the x-axis
		float y_distance = y_length / n; //distance between each vertex on the y-axis
		for (int x = 0; x <= n; x++) {
			for (int y = 0; y <= n ; y++) {
				Vertex point;
				point.x = y * x_distance;
				point.y = glm::linearRand(-1.0f, 1.0f);
				point.z = x * y_distance;
				
				vertices.push_back(point);
			}
		}
		return vertices;

	}

	std::vector<unsigned int> CalculateIndices(std::vector<Vertex> vertices, int n = 4) {
		std::cout << "Calculating Indices " << std::endl;
		std::vector<unsigned int> Indices;
		int size = pow(n, 2) + n - 1;
		
		for (int x = 0; x < size; x++) {
			if ((x+1) % (n+1) == 0 && !Indices.empty()) {
				continue;
			}
			else {
				Indices.push_back(x);
				Indices.push_back(n + 2 + x);
				Indices.push_back(n + 1 + x);
				Indices.push_back(x);
				Indices.push_back(x + 1);
				Indices.push_back(n + 2 + x);
			}
		}
		return Indices;
	}

	void CalculateNormals(std::vector<Vertex> &vertex, const std::vector<unsigned int>& indices, float n = 4) {
		std::cout << "Calculating Normals " << std::endl;
		glm::vec3 p1, p2, p3, normal;
		for (int x = 0; x < indices.size(); x = x+3) {
			p1 = glm::vec3(vertex[indices[x]].x, vertex[indices[x]].y, vertex[indices[x]].z);
			p2 = glm::vec3(vertex[indices[x + 1]].x, vertex[indices[x + 1]].y, vertex[indices[x + 1]].z);
			p3 = glm::vec3(vertex[indices[x + 2]].x, vertex[indices[x + 2]].y, vertex[indices[x + 2]].z);
			normal = glm::cross(p2 - p1, p3 - p1);

			vertex[indices[x]].v_normal[0] = normal.x;
			vertex[indices[x]].v_normal[1] = normal.y;
			vertex[indices[x]].v_normal[2] = normal.z;

			vertex[indices[x + 1]].v_normal[0] = normal.x;
			vertex[indices[x + 1]].v_normal[1] = normal.y;
			vertex[indices[x + 1]].v_normal[2] = normal.z;

			vertex[indices[x + 2]].v_normal[0] = normal.x;
			vertex[indices[x + 2]].v_normal[1] = normal.y;
			vertex[indices[x + 2]].v_normal[2] = normal.z;

		}
		std::cout << "Calculating Normals " << std::endl;
	}

	std::vector<Vertex> GenerateTorusVertex(int radius) {
		std::cout << "Generating Vertexes " << std::endl;
		
		std::vector<Vertex> vertices;
		
		for (int x = 0; x < 12; x++) {
			Vertex point;
			point.x = radius * 2 * glm::cos(30 * x);
			point.y = radius * glm::sin(30 * x);
			point.z = radius * glm::sin(30 * x);

			vertices.push_back(point);
		}

		return vertices;

	}

	std::vector<unsigned int> CalculateTorusIndices(std::vector<Vertex> vertices, int n = 12) { //Under Construction
		std::cout << "Calculating Indices " << std::endl;
		std::vector<unsigned int> Indices;
		int size = pow(n, 2) + n - 1;

		for (int x = 0; x < size; x++) {
			if (x % n == 0 && !Indices.empty()) {
				continue;
			}
			else {
				Indices.push_back(x);
				Indices.push_back(n + 2 + x);
				Indices.push_back(n + 1 + x);
				Indices.push_back(x);
				Indices.push_back(x + 1);
				Indices.push_back(n + 2 + x);
			}
		}
		return Indices;
	}

}

