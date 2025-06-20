#pragma once

#include "Scene.hpp"

#include <iostream>
#include <cassert>

#include <glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <gtc/type_ptr.hpp>                 // value_ptr

namespace udit
{
    
    using namespace std;

    const string Scene::vertex_shader_code =

        "#version 330\n"
        ""
        "uniform mat4 model_view_matrix;"
        "uniform mat4 projection_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec3 vertex_color;"
        ""
        "out vec3 front_color;"
        ""
        "void main()"
        "{"
        "   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   front_color = vertex_color;"
        "}";

    const string Scene::fragment_shader_code =

        "#version 330\n"
        ""
        "in  vec3    front_color;"
        "out vec4 fragment_color;"
        ""
        "void main()"
        "{"
        "    fragment_color = vec4(front_color, 1.0);"
        "}";

    Scene::Scene(unsigned width, unsigned height)
    :
        angle(0)
    {
        // Se establece la configuraci�n b�sica:

        glDisable     (GL_CULL_FACE);
        glEnable    (GL_DEPTH_TEST);
        glClearColor (.1f, .1f, .1f, 1.f);

        // Se compilan y se activan los shaders:

        GLuint program_id = compile_shaders ();

        glUseProgram (program_id);

        model_view_matrix_id = glGetUniformLocation (program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation (program_id, "projection_matrix");

        resize (width, height);
    }

    void Scene::update ()
    {
        angle += 0.01f;
    }

    void Scene::render ()
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Render de los elementos de la escena
        render_Plane   ();
        render_Cone    ();
        render_Cylinder();
    }

    void Scene::render_Plane() 
    {
        //Coloco el plano en escena
        glm::mat4 model_view_matrix_plane(1);
        model_view_matrix_plane = glm::translate(model_view_matrix_plane, glm::vec3(0.f, -0.5f, -1.f));
        model_view_matrix_plane = glm::rotate(model_view_matrix_plane, glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
        model_view_matrix_plane = glm::scale(model_view_matrix_plane, glm::vec3(5.f, 5.f, 5.f));

        glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix_plane));

        //Se dibuja el plano
        plane.render();
    }

    void Scene::render_Cone()
    {
        //Coloco el cono en escena
        glm::mat4 model_view_matrix_cone(1);

        model_view_matrix_cone = glm::translate(model_view_matrix_cone, glm::vec3(-2.f, .5f, -4.f));

        glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix_cone));

        // Se dibuja el cono:
        cone.render();
    }

    void Scene::render_Cylinder()
    {
        //Coloco el cilindro en escena
        glm::mat4 model_view_matrix_cylinder(1);

        model_view_matrix_cylinder = glm::translate(model_view_matrix_cylinder, glm::vec3(2.f, .5f, -4.f));

        glUniformMatrix4fv(model_view_matrix_id, 1, GL_FALSE, glm::value_ptr(model_view_matrix_cylinder));

        // Se dibuja el cilindro:
        cylinder.render();
    }

    void Scene::resize (unsigned width, unsigned height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

        glUniformMatrix4fv (projection_matrix_id, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glViewport (0, 0, width, height);
    }

    GLuint Scene::compile_shaders ()
    {
        GLint succeeded = GL_FALSE;

        // Se crean objetos para los shaders:

        GLuint   vertex_shader_id = glCreateShader (GL_VERTEX_SHADER  );
        GLuint fragment_shader_id = glCreateShader (GL_FRAGMENT_SHADER);

        // Se carga el c�digo de los shaders:

        const char *   vertex_shaders_code[] = {          vertex_shader_code.c_str () };
        const char * fragment_shaders_code[] = {        fragment_shader_code.c_str () };
        const GLint    vertex_shaders_size[] = { (GLint)  vertex_shader_code.size  () };
        const GLint  fragment_shaders_size[] = { (GLint)fragment_shader_code.size  () };

        glShaderSource  (  vertex_shader_id, 1,   vertex_shaders_code,   vertex_shaders_size);
        glShaderSource  (fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);

        // Se compilan los shaders:

        glCompileShader (  vertex_shader_id);
        glCompileShader (fragment_shader_id);

        // Se comprueba que si la compilaci�n ha tenido �xito:

        glGetShaderiv   (  vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (  vertex_shader_id);

        glGetShaderiv   (fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded) show_compilation_error (fragment_shader_id);

        // Se crea un objeto para un programa:

        GLuint program_id = glCreateProgram ();

        // Se cargan los shaders compilados en el programa:

        glAttachShader  (program_id,   vertex_shader_id);
        glAttachShader  (program_id, fragment_shader_id);

        // Se linkan los shaders:

        glLinkProgram   (program_id);

        // Se comprueba si el linkage ha tenido �xito:

        glGetProgramiv  (program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded) show_linkage_error (program_id);

        // Se liberan los shaders compilados una vez se han linkado:

        glDeleteShader (  vertex_shader_id);
        glDeleteShader (fragment_shader_id);

        return (program_id);
    }

    void Scene::show_compilation_error (GLuint shader_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        assert(false);
    }

    void Scene::show_linkage_error (GLuint program_id)
    {
        string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        cerr << info_log.c_str () << endl;

        assert(false);
    }

}
