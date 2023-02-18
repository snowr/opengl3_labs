#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "imgui_utils.h"

struct Vertex3 {
    float x;
    float y;
    float z;
} typedef Vertex3;

class TextureCoordsExample {
public:
    TextureCoordsExample() {
        default_vals();
    }

    float d_t_bottom_left_s = 0.0f;
    float d_t_bottom_left_t = 1.0f;

    float d_t_bottom_right_s = 1.0f;
    float d_t_bottom_right_t = 1.0f;

    float d_t_top_left_s = 1.0f;
    float d_t_top_left_t = 0.5f;

    float d_t_top_right_s = 0.0f;
    float d_t_top_right_t = 0.5f;

    float curr_t_bottom_left_s = d_t_bottom_left_s;
    float curr_t_bottom_left_t = d_t_bottom_left_t;

    float curr_t_bottom_right_s = d_t_bottom_right_s;
    float curr_t_bottom_right_t = d_t_bottom_right_t;

    float curr_t_top_left_s = d_t_top_left_s;
    float curr_t_top_left_t = d_t_top_left_t;

    float curr_t_top_right_s = d_t_top_right_s;
    float curr_t_top_right_t = d_t_top_right_t;

    Vertex3 vertex_a;
    Vertex3 vertex_b;
    Vertex3 vertex_c;
    Vertex3 vertex_d;
    
    void default_vals() {
        curr_t_bottom_left_s = d_t_bottom_left_s;
        curr_t_bottom_left_t = d_t_bottom_left_t;

        curr_t_bottom_right_s = d_t_bottom_right_s;
        curr_t_bottom_right_t = d_t_bottom_right_t;

        curr_t_top_left_s = d_t_top_left_s;
        curr_t_top_left_t = d_t_top_left_t;

        curr_t_top_right_s = d_t_top_right_s;
        curr_t_top_right_t = d_t_top_right_t;

        vertex_a = {.x = -.5f, .y = -.5f, .z = 1.0f};
        vertex_b = {.x = .5f, .y = -.5f, .z = 1.0f};
        vertex_c = {.x = .5f, .y = .5f, .z = 1.0f};
        vertex_d = {.x = -.5f, .y = .5f, .z = 1.0f};
    }

    void full_texture() {
        curr_t_bottom_left_s = 0.0f;
        curr_t_bottom_left_t = 1.0f;

        curr_t_bottom_right_s = 1.0f;
        curr_t_bottom_right_t = 1.0f;

        curr_t_top_left_s = 1.0f;
        curr_t_top_left_t = 0.0f;

        curr_t_top_right_s = 0.0f;
        curr_t_top_right_t = 0.0f;
    }
};

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

void lab3(GLFWwindow* window) {

    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Load the texture
    int width = 32;
    int height = 32;
    unsigned char *image = SOIL_load_image("/home/sina/code/opengl3_labs/Character197.png", &width, &height, 0,
                                           SOIL_LOAD_RGBA);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    imgui_init(window);
    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    TextureCoordsExample ui_state;
    ui_state.d_t_bottom_left_s = 0.0f;
    ui_state.d_t_bottom_left_t = 1.0f;

    ui_state.d_t_bottom_right_s = 1.0f;
    ui_state.d_t_bottom_right_t = 1.0f;

    ui_state.d_t_top_left_s = 1.0f;
    ui_state.d_t_top_left_t = 0.5f;

    ui_state.d_t_top_right_s = 0.0f;
    ui_state.d_t_top_right_t = 0.5f;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

// Start the Dear ImGui frame
        imgui_new_frame();
        bool show_demo_window = true;

        static bool no_menu = false;
        ImGuiWindowFlags window_flags = 0;
        if (!no_menu) window_flags |= ImGuiWindowFlags_MenuBar;

        // Main body of the Demo window starts here.
        if (!ImGui::Begin("Texture Coordinates Control", &show_demo_window, window_flags)) {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            std::cout << "Imgui::End()" << std::endl;
            return;
        }

        ImGui::PushItemWidth(ImGui::GetFontSize() * -12);
        // Menu Bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Menu")) {
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Spacing();
        if (ImGui::CollapsingHeader("Texture Coordinates")) {
            ImGui::Text("Values (s,t):");
            char t_bot_left_s[64] = "";
            sprintf(t_bot_left_s, "%.2f", ui_state.curr_t_bottom_left_s);
            ImGui::InputText("bottom left s", t_bot_left_s, 64, ImGuiInputTextFlags_CharsDecimal);

            static char t_bot_left_t[64] = "";
            sprintf(t_bot_left_t, "%.2f", ui_state.curr_t_bottom_left_t);
            ImGui::InputText("bottom left t", t_bot_left_t, 64, ImGuiInputTextFlags_CharsDecimal);

            ImGui::Spacing();

            static char t_bot_right_s[64] = "";
            sprintf(t_bot_right_s, "%.2f", ui_state.curr_t_bottom_right_s);
            ImGui::InputText("bottom right s", t_bot_right_s, 64, ImGuiInputTextFlags_CharsDecimal);

            static char t_bot_right_t[64] = "";
            sprintf(t_bot_right_t, "%.2f", ui_state.curr_t_bottom_right_t);
            ImGui::InputText("bottom right t", t_bot_right_t, 64, ImGuiInputTextFlags_CharsDecimal);

            ImGui::Spacing();

            static char t_top_left_s[64] = "";
            sprintf(t_top_left_s, "%.2f", ui_state.curr_t_top_left_s);
            ImGui::InputText("top left s", t_top_left_s, 64, ImGuiInputTextFlags_CharsDecimal);

            static char t_top_left_t[64] = "";
            sprintf(t_top_left_t, "%.2f", ui_state.curr_t_top_left_t);
            ImGui::InputText("top left t", t_top_left_t, 64, ImGuiInputTextFlags_CharsDecimal);

            ImGui::Spacing();
            static char t_top_right_s[64] = "";
            sprintf(t_top_right_s, "%.2f", ui_state.curr_t_top_right_s);
            ImGui::InputText("top right s", t_top_right_s, 64, ImGuiInputTextFlags_CharsDecimal);

            static char t_top_right_t[64] = "";
            sprintf(t_top_right_t, "%.2f", ui_state.curr_t_top_right_t);
            ImGui::InputText("top right t", t_top_right_t, 64, ImGuiInputTextFlags_CharsDecimal);

            ui_state.curr_t_bottom_left_s = atof(t_bot_left_s);
            ui_state.curr_t_bottom_left_t = atof(t_bot_left_t);

            ui_state.curr_t_bottom_right_s = atof(t_bot_right_s);
            ui_state.curr_t_bottom_right_t = atof(t_bot_right_t);

            ui_state.curr_t_top_left_s = atof(t_top_left_s);
            ui_state.curr_t_top_left_t = atof(t_top_left_t);

            ui_state.curr_t_top_right_s = atof(t_top_right_s);
            ui_state.curr_t_top_right_t = atof(t_top_right_t);

            bool reset = false;
            reset |= ImGui::Button("Reset");
            if (reset)
            {
                ui_state.default_vals();
            }

            bool load_full = false;
            load_full |= ImGui::Button("Load Full Texture");
            if (load_full)
            {
                ui_state.full_texture();
            }
        }

        ImGui::PopItemWidth();
        ImGui::End();
        // Rendering
        ImGui::Render();

//    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 1.0f);
        glTexCoord2f(ui_state.curr_t_bottom_left_s, ui_state.curr_t_bottom_left_t);
        glVertex3f(ui_state.vertex_a.x, ui_state.vertex_a.y, ui_state.vertex_a.z);

        glTexCoord2f(ui_state.curr_t_bottom_right_s, ui_state.curr_t_bottom_right_t);
        glVertex3f(ui_state.vertex_b.x, ui_state.vertex_b.y, ui_state.vertex_b.z);

        glTexCoord2f(ui_state.curr_t_top_left_s, ui_state.curr_t_top_left_t);
        glVertex3f(ui_state.vertex_c.x, ui_state.vertex_c.y, ui_state.vertex_c.z);

        glTexCoord2f(ui_state.curr_t_top_right_s, ui_state.curr_t_top_right_t);
        glVertex3f(ui_state.vertex_d.x, ui_state.vertex_d.y, ui_state.vertex_d.z);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    SOIL_free_image_data(image);
}

void lab4(GLFWwindow* window)
{
    /////////// VERTEX INPUT
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,

    };
    /////////// VERTEX SHADER
    const char* vertex_shader_source = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";
    GLuint vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    int vertex_shader_compile_success;
    char vs_info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vertex_shader_compile_success);
    if(!vertex_shader_compile_success) {
        glGetShaderInfoLog(vertex_shader, 512, nullptr, vs_info_log);
        std::cout << "Failed to compile vertex shader";
        throw std::runtime_error(vs_info_log);
    }

    /////////// FRAGMENT SHADER
    GLuint fragment_shader;
    const char* fragment_shader_source =
            "#version 400\n"
            "out vec4 frag_colour;"
            "void main() {"
            "  frag_colour = vec4(0.0, 1.0, 0.0, 1.0);"
            "}";
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    int fragment_shader_compile_success;
    char fs_info_log[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fragment_shader_compile_success);
    if(!fragment_shader_compile_success) {
        glGetShaderInfoLog(fragment_shader, 512, nullptr, fs_info_log);
        std::cout << "Failed to compile fragment shader";
        throw std::runtime_error(fs_info_log);
    }

    /////////// SHADER PROGRAM
    GLuint shader_program;
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    int shader_program_link_success;
    char sp_info_log[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &shader_program_link_success);
    if(!shader_program_link_success) {
        glGetProgramInfoLog(shader_program, 512, nullptr, sp_info_log);
        std::cout << "Failed to link shader program";
        throw std::runtime_error(sp_info_log);
    }
    // no longer required post linking
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    /////////// LINKING VERTEX ATTRIBUTES
    GLuint vbo;
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
//    GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
//    GL_STATIC_DRAW: the data is set only once and used many times.
//    GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //      VERTEX 1        |       VERTEX 2        |       VERTEX 3        |
    //  X   |   Y   |   Z   |   X   |   Y   |   Z   |   X   |   Y   |   Z   |
    //0     4       8       12      16      20      24      28      33      36
    // ---------------------> STRIDE: (3 * sizeof(float)) = 12
    // OFFSET: 0
    // The position data is stored as 32-bit (4 byte) floating point values
    // Each position is composed of 3 floats (xyz)
    // There is no space or other values between each set of 3 values. They are tightly
    // packed in the array. If for example we had color values (rgb) then there would be some
    // space between the values.

    // 1. Specifies which vertex attribute we want to configure. Remember in the vertex
    // shader source code we specified `layout (location = 0)`. This sets the location
    // of the vertex attribute to 0.
    // 2. Size of the vertex attribute. It's a vec3, so it's composed of 3 values.
    // 3. Type of data (vec* in GLSL consists of floating point values).
    // 4. Specifies if we want the data to be normalized. Not relevant for this example.
    // 5. Stride - See above diagram. Since this is tightly packed we could have set it to 0.
    // 6. Offset - 0; Not relevant for this example.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    // Each vertex attribute takes data from memory-managed VBO.
    // Which VBO data is taken from is determined by the VBO currently
    // bound to GL_ARRAY_BUFFER when calling `glVertexAttribPointer`.
    // We previously defined the VBO above thus it's bound at this point.
    glEnableVertexAttribArray(0);


    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
}

int main(int argc, char** argv) {
    bool cleanup_imgui = false;
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window and OpenGL context
    GLFWwindow *window = glfwCreateWindow(1200, 1600, "Texture Example", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

//    lab3(window); cleanup_imgui = true;
    lab4(window);
//    lab5(window);

    if(cleanup_imgui) {
        // Clean up
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
