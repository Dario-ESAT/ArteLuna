#ifndef __INPUTS_H__
#define __INPUTS_H__ 1

#include "window.h"
#include <map>
#include <vector>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
class Input {
public:

enum InputKey {
    UNKNOWN = -1,
    SPACE = 32,
    APOSTROPHE = 26,
    COMMA = 51,
    MINUS = 53,
    PERIOD = 52,
    SLASH = 54,
    KEY_0 = 11,
    KEY_1 = 2,
    KEY_2 = 3,
    KEY_3 = 4,
    KEY_4 = 5,
    KEY_5 = 6,
    KEY_6 = 7,
    KEY_7 = 8,
    KEY_8 = 9,
    KEY_9 = 10,
    SEMICOLON = 42,
    EQUAL = 1,
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LEFT_BRACKET = 26,
    BACKSLASH = 41,
    RIGHT_BRACKET= 27,
    GRAVE_ACCENT= 40,
    WORLD_1 = GLFW_KEY_WORLD_1,
    WORLD_2 = GLFW_KEY_WORLD_2,
    ESCAPE = 256,
    ENTER = 28,
    TAB = 15,
    BACKSPACE = 14,
    INSERT = 338,
    DELETE= 338,
    RIGHT= 262,
    LEFT = 263,
    DOWN= 264,
    UP = 265,
    PAGE_UP= 337,
    PAGE_DOWN= 329,
    HOME = 327,
    END= 335,
    CAPS_LOCK= 58,
    SCROLL_LOCK = 281,
    NUM_LOCK = 325,
    PRINT_SCREEN = 311,
    PAUSE = 69,
    F1 = 59,
    F2 = 60,
    F3 = 61,
    F4 = 62,
    F5 = 63,
    F6 = 64,
    F7 = 65,
    F8= 66,
    F9 = 67,
    F10= 68,
    F11 = 87,
    F12 = 88,
    F13= GLFW_KEY_F13,
    F14= GLFW_KEY_F14,
    F15= GLFW_KEY_F15,
    F16 = GLFW_KEY_F16,
    F17 = GLFW_KEY_F17,
    F18 = GLFW_KEY_F18,
    F19= GLFW_KEY_F19,
    F20 = GLFW_KEY_F20,
    F21 = GLFW_KEY_F21,
    F22 = GLFW_KEY_F22,
    F23 = GLFW_KEY_F23,
    F24 = GLFW_KEY_F24,
    F25 = GLFW_KEY_F25,
    KP_0 = 82,
    KP_1 = 79,
    KP_2 = 80,
    KP_3 = 81,
    KP_4 = 75,
    KP_5 = 76,
    KP_6 = 77,
    KP_7 = 71,
    KP_8 = 72,
    KP_9 = 73,
    KP_DECIMAL = 83,
    KP_DIVIDE = 309,
    KP_MULTIPLY = 55,
    KP_SUBSTRACT = 74,
    KP_ADD = 78,
    KP_ENTER = 284,
    KP_EQUAL = 11,
    LEFT_SHIFT = 42,
    LEFT_CONTROL = 29,
    LEFT_ALT = 56,
    LEFT_SUPER = 347,
    RIGHT_SHIFT = 54,
    RIGHT_CONTROL = 285,
    RIGHT_ALT = 312,
    RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    MENU = 349,
    LAST = 335,
};

    Input(std::vector<int> keys);
    ~Input();
    
    bool IsKeyDown(int key);
    bool getIsEnabled() { return is_enabled_; };
    void setEnabled(bool value) { is_enabled_ = value; }

    static void setupKeyInputs(Window& window);

private:
   
   void setIsKeyDown(int key, bool is_down);
   std::map<int, bool> keys_;
   bool is_enabled_;
   static void callback(GLFWwindow* window, int key, int scancode, int 
   action, int mods);
   static std::vector<Input*> instances_;
};


#endif