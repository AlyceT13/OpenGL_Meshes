//Este código es de dominio público
//Alicia Touris Martin

#include "Cylinder.hpp"

namespace udit
{

    Cylinder::Cylinder() : height(2.f), radius(1.f), segments(6)
    {
        create_Cylinder();
        create_Mesh();
    }
    Cylinder::Cylinder(float height, float radius, unsigned segments) : height(height), radius(radius), segments(segments)
    {
        create_Cylinder();
        create_Mesh();
    }

    Cylinder::~Cylinder()
    {
        // Se liberan los VBOs y el VAO usados:

        glDeleteVertexArrays(1, &vao_id);
        glDeleteBuffers(VBO_COUNT, vbo_ids);
    }

    void Cylinder::create_Cylinder()
    {
        coordinates.clear();
        colors.clear();
        indices.clear();
        normals.clear();

        float angle_step = (2.f * M_PI) / segments;

        // Centro superior e inferior
        coordinates.emplace_back(0.f, height / 2.f, 0.f);
        colors.emplace_back(.6f, .4f, 1.f);
        normals.emplace_back(0.f, 1.f, 0.f);

        coordinates.emplace_back(0.f, -height / 2.f, 0.f);
        colors.emplace_back(.4f, .4f, 1.f);
        normals.emplace_back(0.f, -1.f, 0.f);

        // Vertices de las bases superiores e inferiores
        for (unsigned i = 0; i < segments; ++i)
        {
            float angle = i * angle_step;
            float x = radius * cos(angle);
            float z = radius * sin(angle);

            // Base superior
            coordinates.emplace_back(x, height / 2.0f, z);
            colors.emplace_back(.4f, .9f, 1.f);
            normals.emplace_back(0.f, 1.f, 0.f);

            // Base inferior
            coordinates.emplace_back(x, -height / 2.0f, z);
            colors.emplace_back(.4f, 1.f, .6f);
            normals.emplace_back(0.f, -1.f, 0.f);
        }

        // indices base superior
        for (unsigned i = 0; i < segments; ++i)
        {
            unsigned next = (i + 1) % segments;
            indices.push_back(0);
            indices.push_back(2 + i * 2);
            indices.push_back(2 + next * 2);
        }

        // Indices base inferior
        for (unsigned i = 0; i < segments; ++i)
        {
            unsigned next = (i + 1) % segments;
            indices.push_back(1);                 
            indices.push_back(3 + next * 2);  
            indices.push_back(3 + i * 2);
        }

        // Indices laterales
        for (unsigned i = 0; i < segments; ++i)
        {
            unsigned next = (i + 1) % segments;

            indices.push_back(2 + i * 2); 
            indices.push_back(3 + i * 2);
            indices.push_back(2 + next * 2);

            indices.push_back(3 + i * 2); 
            indices.push_back(3 + next * 2); 
            indices.push_back(2 + next * 2);
        }
    }
}