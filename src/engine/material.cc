#include "..\..\include\engine\material.h"
#include "comon_defs.h"
#include <memory>


Material::Material()
{

}

Material::Material(char* vert, char* frag)
{
	shader_.Init(vert, frag);
	program_.Init(shader_.vertex_, shader_.fragment_);

}

Material::~Material()
{
}
