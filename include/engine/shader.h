#ifndef __SHADER_H__
#define __SHADER_H__ 1

class Shader {
public:
    Shader();
    Shader(const char* vertex, const char* fragment);
    Shader(const char* vertex, const char* fragment, const char* geometry);
    ~Shader();
    void Init(const char* vertex, const char* fragment);
    void Init(const char* vertex, const char* fragment, const char* geometry);
    unsigned int vertex();
    unsigned int fragment();
    unsigned int geometry();
    unsigned int vertex_;
    unsigned int fragment_;
private:

    unsigned int geometry_;
};


#endif