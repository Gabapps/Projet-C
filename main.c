#include <stdlib.h>
#include <stdio.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "SceneObject.h"
#include "Shader.h"
#include "Mesh.h"
#include "Math.h"

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

int main(void)
{
	window_open();
    glfwSetErrorCallback(error_callback);
    glfwMakeContextCurrent(window_get());
    glfwSetKeyCallback(window_get(), key_callback);

    glewExperimental=GL_FALSE;
    GLenum error = glGetError();

    if (error != GL_NO_ERROR)
    {
        printf("OpenGL Error: %d\n", error);
    }
    GLenum glewinit = glewInit();
    if (glewinit != GLEW_OK) {
        printf("Glew's not okay! %s\n", glewGetErrorString(glewinit));
        exit(EXIT_FAILURE);
    }
    if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
    	exit(EXIT_FAILURE);

    // Scene script init
    Shader shader = {"Shaders/vertex.vert", "Shaders/fragment.frag",0,0,0};
    shader_load(&shader);

    Mesh mesh;
    mesh_load_from_obj(&mesh, "Models/Tank.obj");

    SceneObject *tank = so_create("Tank", transform_origin());
    //tank->scripts;
    tank->mesh = &mesh;
    tank->shader = &shader;

    Camera cam;
    camera_init(&cam);
    vec3 pos = {-10,3,-10},
    	center = {0,0,0},
		up = {0,1,0};
    vec3_add(cam.transform.position, cam.transform.position, pos);

    // Scene script stop

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window_get()))
    {
    	camera_refresh_matrices(&cam);
    	transform_look_at(&(cam.transform),pos, center,up);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On vide les tampons couleurs et profondeur

    	so_draw(tank, &cam);

        glfwSwapBuffers(window_get());
        glfwPollEvents();
    }

    mesh_free(&mesh);

    glfwDestroyWindow(window_get());
    glfwTerminate();
    return 0;
}
