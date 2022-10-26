#ifndef __SHADER_H__
#define __SHADER_H__ 1

#include "stdint.h"
#include "window.h"
#include "glad/gl.h"
#include <string>
#include "GLFW/glfw3.h"


class shader {
public:

    shader(const char* vertex, const char* fragment);
    shader(const char* vertex, const char* fragment, const char* geometry);
    ~shader();
    int vertex();
    int fragment();
    int geometry();
private:
    int vertex_;
    int fragment_;
    int geometry_;
};


#endif