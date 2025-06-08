//Este código es de dominio público
//Alicia Touris Martin

#pragma once

#ifndef CONE_HEADER
#define CONE_HEADER
#define _USE_MATH_DEFINES

#include "Mesh.hpp"
#include <cmath>
#include <glad/glad.h>

namespace udit
{
    class Cone : public Mesh
    {
    private:

        //Variables del cono
        float height, radius;
        unsigned segments;

        void create_Cone();

    public:

        Cone();
        Cone(float height, float radius, unsigned segments);
        ~Cone();

    };

}
#endif