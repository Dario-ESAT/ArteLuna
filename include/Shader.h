#ifndef __SHADER_H__
#define __SHADER_H__ 1

class Shader {
public:

    Shader(const char* vertex, const char* fragment);
    Shader(const char* vertex, const char* fragment, const char* geometry);
    ~Shader();
    int vertex();
    int fragment();
    int geometry();
private:
    int vertex_;
    int fragment_;
    int geometry_;
};


#endif