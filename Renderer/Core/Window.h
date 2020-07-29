/* date = July 29th 2020 0:21 am */
#pragma once

#include <GLFW/glfw3.h>

#include <string>

#define OPENGL_MAJOR 4
#define OPENGL_MINOR 0

struct Window
{
    public:
    std::string name = "";
    uint32_t width;
    uint32_t height;
    GLFWwindow* window_handle = nullptr;
    int32_t viewport_width;
	int32_t viewport_height;
	
    private:
    bool is_open = true;
    
    public:
    Window(uint32_t width, uint32_t height, const std::string& window_name);
    Window(uint32_t width, uint32_t height, std::string&& window_name);
    ~Window();
    bool IsOpen();
	void MakeContextCurrent();
	void MakeContextNonCurrent();
    
    private:
    /*Handles creating the GLFW window regardless of what constructor was used*/
    void CreateWindow();
    /*Polls Window Events*/
    void PollEvents();
    
};