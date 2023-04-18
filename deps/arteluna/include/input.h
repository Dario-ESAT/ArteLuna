#ifndef __INPUTS_H__
#define __INPUTS_H__ 1

#include "window.h"
#include <map>
#include <vector>
#include "glad/gl.h"
#include "GLFW/glfw3.h"
namespace al{
  enum InputKeyboard
  {
    UNKNOWN = -1,
    SPACE = 32,
    APOSTROPHE = 26,
    COMMA = 44,
    MINUS = 47,
    PERIOD = 46,
    SLASH = 54,
    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,
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
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8= 297,
    F9 = 298,
    F10= 299,
    F11 = 300,
    F12 = 301,
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
    KP_0 = 320,
    KP_1 = 321,
    KP_2 = 322,
    KP_3 = 323,
    KP_4 = 324,
    KP_5 = 325,
    KP_6 = 326,
    KP_7 = 327,
    KP_8 = 328,
    KP_9 = 339,
    KP_DECIMAL = 330,
    KP_DIVIDE = 331,
    KP_MULTIPLY = 332,
    KP_SUBSTRACT = 333,
    KP_ADD = 334,
    KP_ENTER = 334,
    KP_EQUAL = 11,
    LEFT_SHIFT = 340,
    LEFT_CONTROL = 341,
    LEFT_ALT = 342,
    LEFT_SUPER = 280,
    RIGHT_SHIFT = 344,
    RIGHT_CONTROL = 345,
    RIGHT_ALT = 346,
    RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
    MENU = 349,
    LAST = 335,
  };

  enum CursorMode {
    NORMAL = GLFW_CURSOR_NORMAL,
    HIDDEN = GLFW_CURSOR_HIDDEN,
    DISABLED = GLFW_CURSOR_DISABLED,
  };

  class Input {
  public:
    Input(std::vector<int> keys);
    ~Input();
    bool IsMouseButtonDown(int button);
    bool IsKeyDown(int key);
    bool enabled() const { return enabled_; }
    void setEnabled(bool value) { enabled_ = value; }
    void setMouseMode(CursorMode mode);
    glm::vec<2,double> cursor_pos() const {return cursor_pos_;}

    static void get_scrollback(::GLFWwindow* window, double xoffset, double yoffset);

    static float scrollback_y_value_;
    static float scrollback_x_value_;
  private:
    void setupInput(::GLFWwindow& window);
    void setIsKeyDown(int key, bool is_down);
    void setIsMouseDown(int key, bool is_down);

    static void keyboard_callback(::GLFWwindow* window, int key, int scancode,
     int action, int mods);
    static void mouse_button_callback(::GLFWwindow* window, int button, int action, 
    int mods);
    static void cursor_pos_callback(::GLFWwindow* window, double xpos, double ypos);
  
    bool enabled_;
    std::map<int, bool> keyboards_keys_;
    std::map<int, bool> mouse_keys_;
    static std::vector<Input*> instances_;
    ::GLFWwindow* window_ref_;
    glm::vec<2,double> cursor_pos_;
  
    friend class Window;
  };
}
#endif