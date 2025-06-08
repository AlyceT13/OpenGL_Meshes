//Este código es de dominio público
//Alicia Touris Martin

#include "Plane.hpp"

namespace udit
{
    Plane::Plane() : width(2.f), height(2.f), columns(4), rows(4)
    {
        create_Plane();
        create_Mesh();
    }

    Plane::Plane(float width, float height, unsigned columns, unsigned rows) : width(width), height(height), columns(columns), rows(rows)
    {
        create_Plane();
        create_Mesh();
    }

    Plane::~Plane()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Plane::create_Plane()
    {
        coordinates.clear();
        colors.clear();
        indices.clear();
        normals.clear();

        coordinates.reserve((columns + 1) * (rows + 1));
        normals.reserve((columns + 1) * (rows + 1));

        glm::vec3 vertex = glm::vec3{ -width / 2.f, -height / 2.f, 0.f };

        float tileWidth = width / float(columns);
        float tileHeight = height / float(rows);

        for (unsigned i = 0; i <= rows; ++i)
        {
            for (unsigned j = 0; j <= columns; ++j)
            {
                coordinates.push_back(vertex);
                normals.push_back({ 0.f, 0.f, 1.f });

                // Se asigna un color dependiendo de la posición de los vertices
                glm::vec3 color = glm::vec3(float(j) / columns, float(i) / rows, 1.0f);
                colors.push_back(color);

                vertex.x += tileWidth;
            }
            vertex.x = -width / 2.f;
            vertex.y += tileHeight;
        }

        for (unsigned i = 0; i < rows; ++i)
        {
            for (unsigned j = 0; j < columns; ++j)
            {
                unsigned topLeft = i * (columns + 1) + j;
                unsigned topRight = topLeft + 1;
                unsigned bottomLeft = (i + 1) * (columns + 1) + j;
                unsigned bottomRight = bottomLeft + 1;

                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);

                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }
    }
}