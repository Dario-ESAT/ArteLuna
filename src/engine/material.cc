#include "..\..\include\engine\material.h"
#include "comon_defs.h"
#include "components/transform_component.h"
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

void Material::Init(char* vert, char* frag)
{
	shader_.Init(vert, frag);
	program_.Init(shader_.vertex_, shader_.fragment_);
}

void Material::set_uniform_value(const float* unif, int type, const int uniform_pos)
{
	program_.useProgram();
	switch (type) {
	case 1:
		//GLint myLoc = glGetUniformLocation(program_.getProgram(), "t_matrix");
		glUniform1f(uniform_pos, unif[0]);
		break;

	case 2:
		glUniform2f(uniform_pos, unif[0], unif[1]);
		break;

	case 3:
		glUniform3f(uniform_pos, unif[0], unif[1], unif[2]);
		break;

	case 4:
		glUniformMatrix4fv(uniform_pos, 1, false, unif);
		break;
	}
}
