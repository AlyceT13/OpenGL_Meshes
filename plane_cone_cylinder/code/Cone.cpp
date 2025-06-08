//Este código es de dominio público
//Alicia Touris Martin

#include "Cone.hpp"

namespace udit
{
    Cone::Cone() : height(2.f), radius(1), segments(6)
    {
        create_Cone();
        create_Mesh();
    }

    Cone::Cone(float height, float radius, unsigned segments) : height(height), radius(radius), segments(segments)
    {
        create_Cone();
        create_Mesh();
    }

    Cone::~Cone()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Cone::create_Cone()
    {
        coordinates.clear();
        colors.clear();
        indices.clear();
        normals.clear();

        // Punta del cono
        glm::vec3 tip(0.0f, height / 2.f, 0.f);
        coordinates.push_back(tip);
        colors.push_back(glm::vec3(.6f, 1.f, 1.f));

        // Centro de la base del cono
        glm::vec3 base_center(0.0f, -height / 2.f, 0.f);
        coordinates.push_back(base_center);
        colors.push_back(glm::vec3(1.f, 0.f, 1.f));

        // Vertices de la base
        float angle_step = (2.0f * M_PI) / segments;
        for (unsigned i = 0; i < segments; ++i)
        {
            float angle = i * angle_step;
            glm::vec3 vertex(radius * cos(angle), -height / 2.0f, radius * sin(angle));
            coordinates.push_back(vertex);
            colors.push_back(glm::vec3(.5f, .5f, 1.f));
        }

        // Indices para los lados del cono
        for (unsigned i = 0; i < segments; ++i)
        {
            unsigned next = (i + 1) % segments;
            indices.push_back(0);               // Punta del cono
            indices.push_back(2 + i);           // Vertice actual de la base
            indices.push_back(2 + next);        // Siguiente vertice de la base

            // Calcular normales de los triangulos laterales
            glm::vec3 edge1 = coordinates[2 + i] - coordinates[0];
            glm::vec3 edge2 = coordinates[2 + next] - coordinates[0];
            glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

            // Normales de los vertices
            normals.push_back(normal);
            normals.push_back(normal);
            normals.push_back(normal);
        }

        // Indices de la base
        for (unsigned i = 0; i < segments; ++i)
        {
            unsigned next = (i + 1) % segments;
            indices.push_back(1);               // Centro de la base
            indices.push_back(2 + next);        // Siguiente vertice de la base
            indices.push_back(2 + i);           // Actual vertice de la base

            // Normales de la base
            normals.push_back(glm::vec3(0.f, -1.f, 0.f));
            normals.push_back(glm::vec3(0.f, -1.f, 0.f));
            normals.push_back(glm::vec3(0.f, -1.f, 0.f));
        }
    }
}