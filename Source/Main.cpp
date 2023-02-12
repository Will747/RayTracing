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

    // Setup Glfw and OpenGL backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    
    Viewport mainViewport(300, 300);

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

        // Render the viewport
        static std::string viewportTitle = "Viewport";
    	ImGui::Begin(viewportTitle.c_str(), NULL);

        mainViewport.UpdateTexture();

        std::shared_ptr<Texture> image = mainViewport.GetTexture();
        ImGui::Image((void*)(intptr_t)image->GetTextureID(), image->GetDimensions());
        ImGui::End();

        // Render the controls window
        ImGui::Begin("Controls");
        ImGui::ColorEdit3("Background Colour", (float*) &mainViewport.bgColour);
        ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
            ImGui::GetIO().Framerate);
        ImGui::End();

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
