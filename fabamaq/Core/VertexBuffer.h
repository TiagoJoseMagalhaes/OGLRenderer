/* date = August 1st 2020 5:04 pm */
#pragma once
#include <cstdint>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

struct Vertex
{
	const glm::vec3 position;
	const glm::vec2 uv;

public:
	Vertex(const glm::vec3& position, const glm::vec2& uv) :position(position), uv(uv) {};

	// this function define the vertex data layout for opengl, in this case we have a 3 position floats and 2 texture coordinate floats
	void SetVertexAttributes(uint32_t layout_slot = 0)
	{
		// TODO(Tiago): name it base layout slot?
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
};

template<typename vertex_type>
struct VertexBuffer
{
public:
	uint32_t vertex_buffer_object = 0;
	uint32_t vertex_attribute_array_object = 0;
	std::vector<vertex_type> vertices;

public:
	VertexBuffer() = default;
	VertexBuffer(const std::vector<vertex_type>& vertices, uint32_t layout_slot = 0)
		:vertices(vertices)
	{
		//creates the opengl VBO and VAO
		glGenVertexArrays(1, &this->vertex_attribute_array_object);
		glBindVertexArray(this->vertex_attribute_array_object);

		//Binds the VAO and VBO
		glGenBuffers(1, &this->vertex_buffer_object);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_object);

		//Copies data into the VBO
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_type), vertices.data(), GL_STATIC_DRAW);

		//Records the vertex configuration data into the VAO
		this->vertices[0].SetVertexAttributes(layout_slot);
	}

	void Bind()
	{
		// NOTE(Tiago): Binds the VBO containing the vertex configuration data for usage
		glBindVertexArray(this->vertex_attribute_array_object);
	}

	void Draw()
	{
		// TODO(Tiago): Support for non-triangle-based vbos
		glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
	}
};

