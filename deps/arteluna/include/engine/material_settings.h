#ifndef H_MATERIAL_SETTINGS_
#define H_MATERIAL_SETTINGS_ 1

#include <map>
#include <string>
#include <vector>

#include "shader.h"
#include "program.h"
#include "texture.h"

class MaterialSettings {
  
public:
  MaterialSettings();
  ~MaterialSettings();
  
  virtual void use() = 0;
  

private:
 
};


#endif