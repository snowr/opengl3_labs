#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "imgui_utils.h"

void lab1() {
    glBegin(GL_LINES);

    glPointSize(50.f);
    glColor3f(0, 1, 0);

    glVertex3f( -1.0f,0.0f, 1.0f);
    glVertex3f(1.0f,0.0f, 1.0f);

    glEnd();
    glFlush();
}

void lab2() {
    glBegin(GL_LINES);

    glColor3f(0, 1, 0);

    glVertex3f( -.5f,0.0f, 1.0f);
    glVertex3f(1.0f,0.0f, 1.0f);

    glEnd();

    glPointSize(5.f);
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    glVertex3f( -.5f,0.0f, 1.0f);
    glEnd();

    glFlush();
}

void lab3() {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f(-.5f,-.5f, 1.0f);

    glTexCoord2f(1.0f, 1.0f);
//    glTexCoord2f(0.5, 0.5f);
    glVertex3f( .5f,-.5f, 1.0f);

//    glTexCoord2f(1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.5f);
    glVertex3f( .5f, .5f, 1.0f);

//    glTexCoord2f(0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.5f);
    glVertex3f(-.5f, .5f, 1.0f);
    glEnd();
}


void lab99() {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(-1.0f,-1.0f, 1.0f);
    glVertex3f(-.5f,-.5f, 1.0f);

    glTexCoord2f(1.f, 1.f);
    glVertex3f( .5f,-.5f, 1.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( .5f, .5f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-.5f, .5f, 1.0f);
    glEnd();
}

int main(int argc, char** argv) {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create a window and OpenGL context
    GLFWwindow* window = glfwCreateWindow(1200, 1600, "Texture Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Load the texture
    int width = 32;
    int height = 32;
    unsigned char* image = SOIL_load_image("/home/sina/code/opengl3_labs/Character197.png", &width, &height, 0, SOIL_LOAD_RGBA);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    imgui_init(window);
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
//        ImGui_ImplSDL2_ProcessEvent(&event);
//        ImGui_ImplOpenGL3
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Start the Dear ImGui frame
        imgui_new_frame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);
        // Rendering
        ImGui::Render();

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//        lab2();
        lab3();
//        lab99();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    ImGui_ImplOpenGL3_Shutdown();
    ImGui::DestroyContext();

    SOIL_free_image_data(image);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
