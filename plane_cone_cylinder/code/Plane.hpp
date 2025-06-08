//Este código es de dominio público
//Alicia Touris Martin

#pragma once

#ifndef PLANE_HEADER
#define PLANE_HEADER

#include "Mesh.hpp"
#include <glad/glad.h>

namespace udit
{
    class Plane : public Mesh
    {

    private:

        //Variables del plano
        float width, height;
        unsigned columns, rows;

        void create_Plane();

    public:

        Plane(); //Constructor por defecto
        Plane(float width, float height, unsigned columns, unsigned rows);
        ~Plane();

    };
}

#endif
