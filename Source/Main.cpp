#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Viewport.h"

// Based off example included with ImGui
int main()
{
    glfwInit();

    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Setup scaling for high DPI monitors
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    float scale, yScale;
    glfwGetMonitorContentScale(monitor, &scale, &yScale);

    if (scale > 1)
    {
        glfwWindowHint(GLFW_SCALE_TO_MONITOR, GL_TRUE);
    }

    constexpr int window_width = 1280;
    constexpr int window_height = 720;
    const std::string window_title = "Ray Tracing Demo";

    // Create new window and check it is valid
    GLFWwindow* window =
        glfwCreateWindow(window_width, window_height, window_title.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Could not create window!" << std::endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL();

    // Ensures the context isn't updating faster than the monitor.
    glfwSwapInterval(1);

    // Setup ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup ImGui Style
    ImGui::StyleColorsDark();
    ImGuiStyle& Style = ImGui::GetStyle();
    Style.ScaleAllSizes(scale);

    // Setup Glfw and OpenGL backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Add font that will scale for high DPI display
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f * scale);

    // Enable docking
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    
    Viewport mainViewport(500, 500);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        // Processes any pending events
        glfwPollEvents();

        // Set window background colour
        glClear(GL_COLOR_BUFFER_BIT);

        // Begin ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport();

        // Render the viewport
        static std::string viewportTitle = "Viewport";
    	ImGui::Begin(viewportTitle.c_str(), NULL);

        mainViewport.UpdateTexture();

        std::shared_ptr<Texture> image = mainViewport.GetTexture();
        ImGui::Image((void*)(intptr_t)image->GetTextureID(), image->GetDimensions());
        ImGui::End();

        // Render the viewport controls
        mainViewport.DrawUI();

        // Render all ImGui items
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
    // Cleanup glfw
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
