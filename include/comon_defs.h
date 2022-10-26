#ifndef __COMON_DEFS_H__
#define __COMON_DEFS_H__ 1



struct Vtx {
	float x, y, z;
	float r, g, b;
	unsigned int u,v;
};

enum errors {
	program_error = -1
	shader_error = -2,
};


#endif