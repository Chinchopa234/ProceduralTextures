#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


int main()
{
    // -----------------------------------------------------
    // GLFW initialization
    // -----------------------------------------------------

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return 1;
    }

    // Request OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    // Required for OpenGL 3.2+ core profile on macOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    // -----------------------------------------------------
    // Create window
    // -----------------------------------------------------

    GLFWwindow* window = glfwCreateWindow(
        1280,
        720,
        "Procedural Texture Generator",
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // VSync

    // -----------------------------------------------------
    // Initialize OpenGL
    // -----------------------------------------------------

    int version = gladLoadGL(glfwGetProcAddress);

    if (version == 0)
    {
        std::cerr << "Failed to initialize OpenGL\n";

        glfwDestroyWindow(window);
        glfwTerminate();

        return 1;
    }

    std::cout
        << "OpenGL version: "
        << glGetString(GL_VERSION)
        << '\n';

    // -----------------------------------------------------
    // Initialize Dear ImGui
    // -----------------------------------------------------

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    ImGui::StyleColorsDark();

    // GLFW backend
    ImGui_ImplGlfw_InitForOpenGL(window, true);

    // OpenGL 3 backend
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // -----------------------------------------------------
    // Main loop
    // -----------------------------------------------------

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        // Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // -------------------------------------------------
        // Test window
        // -------------------------------------------------

        ImGui::Begin("Procedural Texture Generator");

        ImGui::Text("C++20 + GLFW + OpenGL 3.3 + Dear ImGui");

        ImGui::Separator();

        ImGui::Text("Project is working!");

        static float frequency = 1.0f;
        static float amplitude = 1.0f;

        ImGui::SliderFloat(
            "Frequency",
            &frequency,
            0.1f,
            20.0f
        );

        ImGui::SliderFloat(
            "Amplitude",
            &amplitude,
            0.0f,
            2.0f
        );

        static int noiseType = 0;

        const char* noiseTypes[] =
        {
            "Perlin",
            "Voronoi"
        };

        ImGui::Combo(
            "Noise type",
            &noiseType,
            noiseTypes,
            IM_ARRAYSIZE(noiseTypes)
        );

        if (ImGui::Button("Generate"))
        {
            std::cout << "Generate button pressed\n";
        }

        ImGui::SameLine();

        if (ImGui::Button("Save"))
        {
            std::cout << "Save button pressed\n";
        }

        ImGui::End();

        // -------------------------------------------------
        // Rendering
        // -------------------------------------------------

        ImGui::Render();

        int displayWidth;
        int displayHeight;

        glfwGetFramebufferSize(
            window,
            &displayWidth,
            &displayHeight
        );

        glViewport(
            0,
            0,
            displayWidth,
            displayHeight
        );

        glClearColor(
            0.1f,
            0.1f,
            0.1f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(
            ImGui::GetDrawData()
        );

        glfwSwapBuffers(window);
    }

    // -----------------------------------------------------
    // Cleanup
    // -----------------------------------------------------

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();

    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}