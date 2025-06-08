//Este código es de dominio público
//Alicia Touris Martin

#pragma once

#ifndef MESH_HEADER
#define MESH_HEADER

#include <vector>
#include <glm.hpp>
#include <glad/glad.h>

namespace udit
{
    class Mesh
    {

    protected:
        // Índices para indexar el array vbo_ids:
        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            INDICES_EBO,
            VBO_COUNT
        };
        // Vectores de datos:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec3> colors;
        std::vector<glm::vec3> normals;
        std::vector<GLuint> indices;

        void create_Mesh();

        GLuint vbo_ids[VBO_COUNT];      // Ids de los VBOs que se usan
        GLuint vao_id;                  // Id del VAO de la mesh

    public:
        Mesh(); //Constructor por defecto
        ~Mesh();

        void render();
    };

}

#endif