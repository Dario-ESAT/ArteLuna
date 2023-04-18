#ifndef __SHADER_H__
#define __SHADER_H__ 1
#include <cstdint>
namespace al{
  class Shader {
  public:
    Shader();
    Shader(const char* vertex, const char* fragment);
    Shader(const char* vertex, const char* fragment, const char* geometry);
    ~Shader();
    void Init(const char* vertex, const char* fragment);
    void Init(const char* vertex, const char* fragment, const char* geometry);
    uint32_t vertex() const;
    uint32_t fragment() const;
    uint32_t geometry() const;
  private:

    uint32_t vertex_;
    uint32_t fragment_;
    uint32_t geometry_;
  };
}
#endif