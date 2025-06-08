#pragma once

#ifndef CYLINDER_HEADER
#define CYLINDER_HEADER
#define _USE_MATH_DEFINES

#include "Mesh.hpp"
#include <cmath>
#include <glad/glad.h>

namespace udit
{
    class Cylinder : public Mesh
    {
    private:

        //Variables del cono
        float height, radius;
        unsigned segments;

        void create_Cylinder();

    public:

        Cylinder();
        Cylinder(float height, float radius, unsigned segments);
        ~Cylinder();

    };

}

#endif
