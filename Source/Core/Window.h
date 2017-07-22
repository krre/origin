#pragma once
#include <string>

struct SDL_Window;

class Window {

public:
    Window();
    ~Window();

    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }

    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setTitle(const std::string& title) { this->title = title; }
    std::string getTitle() const { return title; }

    void show();

private:
    SDL_Window* handle = nullptr;
    int x = 0;
    int y = 0;
    int width = 800;
    int height = 600;
    std::string title = "Untitled";

    void create();
};
