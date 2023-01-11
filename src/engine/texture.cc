#include "..\..\include\engine\texture.h"
#include "comon_defs.h"
#include <memory>


Texture::Texture() {
	width_ = 0;
	height_ = 0;
	depth_ = 0;
	min_filter_ = Linear;
	mag_filter_ = Linear;
}

Texture::Texture(int w, int h, Filter mag_filter, Filter min_filter, Format format, std::vector<uint8_t> data_texture)
{
	width_ = 0;
	height_ = 0;
	depth_ = 0;
	min_filter_ = min_filter;
	mag_filter_ = mag_filter;
	format_ = format;
	texture_ = data_texture;
}


Texture::~Texture() {

}

void Texture::SetData(Filter mag_filter, Filter min_filter, Format format)
{
	switch (mag_filter)
	{
	case Linear:

	default:
		break;
	}
}
