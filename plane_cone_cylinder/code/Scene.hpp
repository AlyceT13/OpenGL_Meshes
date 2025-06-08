#pragma once

#include "Plane.hpp"
#include "Cone.hpp"
#include "Cylinder.hpp"
#include <string>

namespace udit
{

    class Scene
    {
    private:

        static const std::string   vertex_shader_code;
        static const std::string fragment_shader_code;

        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;

        Plane    plane = Plane(3.f,3.f,6.f,6.f);
        Cone     cone = Cone(2.f, 1.f, 12.f);
        Cylinder cylinder = Cylinder(2.f, 1.f, 12.f);
        float    angle;

    public:

        Scene(unsigned width, unsigned height);

        void   update ();
        void   render ();
        void   resize (unsigned width, unsigned height);

    private:

        GLuint compile_shaders        ();
        void   show_compilation_error (GLuint  shader_id);
        void   show_linkage_error     (GLuint program_id);
        void   render_Plane           ();
        void   render_Cone            ();
        void   render_Cylinder        ();
    };

}
