#ifndef __INPUTS_H__
#define __INPUTS_H__ 1

#include "window.h"
#include <map>
#include <vector>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
class Inputs {
public:

enum InputKey {
    UNKNOWN = -1,
    SPACE = 57,
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
    A = 30,
    B = 48,
    C = 46,
    D = 32,
    E = 18,
    F = 33,
    G = 34,
    H = 35,
    I = 23,
    J = 36,
    K = 37,
    L = 38,
    M = 50,
    N = 49,
    O = 24,
    P = 25,
    Q = 81,
    R = 82,
    S = 31,
    T = 20,
    U = 22,
    V = 47,
    W = 17,
    X = 45,
    Y = 21,
    Z = 44,
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
    RIGHT= 333,
    LEFT = 331,
    DOWN= 336,
    UP = 328,
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
    KP_LEFT_SHIFT = 42,
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

    Inputs(std::vector<int> keys);
    ~Inputs();
    
    bool IsKeyDown(int key);
    bool getIsEnabled() { return is_enabled_; };
    bool setEnabled(bool value) { is_enabled_ = value; };

    static void setupKeyInputs(Window& window);

private:
   
   void setIsKeyDown(int key, bool is_down);
   std::map<int, bool> keys_;
   bool is_enabled_;
   static void callback(class GLFWwindow* window, int key, int scancode, int action, int mods);
   static std::vector<Inputs*> instances_;
};


#endif