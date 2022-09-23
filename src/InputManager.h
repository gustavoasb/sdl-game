#ifndef _INPUT_MANAGER_H
#define _INPUT_MANAGER_H

#include <vector>
#include <unordered_map>
#include <SDL2/SDL.h>

#define LEFT_ARROW_KEY    SDLK_LEFT 
#define RIGHT_ARROW_KEY   SDLK_RIGHT 
#define UP_ARROW_KEY      SDLK_UP 
#define DOWN_ARROW_KEY    SDLK_DOWN 
#define ESCAPE_KEY        SDLK_ESCAPE 
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

class InputManager{
  private:
    InputManager();
    ~InputManager();
    
    std::vector<bool> mouseState;
    std::vector<int> mouseUpdate;

    bool quitRequested;
    int updateCounter;

    int mouseX;
    int mouseY;

    std::unordered_map<int, bool> keyState; 
    std::unordered_map<int, int> keyUpdate; 
  public:
    void Update();

    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager& GetInstance();
};

#endif