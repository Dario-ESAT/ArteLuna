#include "..\..\include\engine\texture.h"
#include "comon_defs.h"
#include <glad/gl.h>
#include <memory>


Texture::Texture() {
	width_ = 0;
	height_ = 0;
	depth_ = 0;
	min_filter_ = Linear;
	mag_filter_ = Linear;
	type_ = T_2D;

	
}

Texture::Texture(int w, int h, int d, Filter mag_filter, Filter min_filter, Format format, Type type)
{
	width_ = w;
	height_ = h;
	depth_ = d;
	min_filter_ = min_filter;
	mag_filter_ = mag_filter;
	format_ = format;
	
	type_ = type;
	try {
		glGenTextures(1, &id_texture_);
		throw 10;
		glActiveTexture(GL_TEXTURE0 + id());
		throw 11;
		switch (type_) {
		case Type::T_1D:
			glBindTexture(GL_TEXTURE_1D, id());
			break;
		case Type::T_2D:
			glBindTexture(GL_TEXTURE_2D, id());
			break;
		case Type::T_3D:
			glBindTexture(GL_TEXTURE_3D, id());
			break;
		}
		throw 12;
	}
	catch(int e){
		if (e == 10) {
			printf("There was an error on the textue, %d", e);
		}
		if (e == 11) {
			printf("There was an error on the textue, %d", e);
		}
		if (e == 12) {
			printf("There was an error on the textue, %d", e);
		}
	}
}



Texture::~Texture() {

}

void Texture::set_texture(std::vector<uint8_t> data_texture, int w, int h, int d, Filter mag_filter, Filter min_filter, Format format, Type type)
{
	texture_ = data_texture;

	try {
		if(id() != 0)
			glGenTextures(1, &id_texture_);

		glActiveTexture(GL_TEXTURE0 + id());

		switch (type_) {
		case Type::T_1D:
			glBindTexture(GL_TEXTURE_1D, id());
			break;
		case Type::T_2D:
			glBindTexture(GL_TEXTURE_2D, id());
			break;
		case Type::T_3D:
			glBindTexture(GL_TEXTURE_3D, id());
			break;
		}
	}
	catch (int e) {
		if (e == 10) {
			printf("There was an error on the textue, %d", e);
		}
		if (e == 11) {
			printf("There was an error on the textue, %d", e);
		}
		if (e == 12) {
			printf("There was an error on the textue, %d", e);
		}
	}
}

void Texture::SetData(Filter mag_filter, Filter min_filter, Format format, Wrap ws, Wrap wt, Wrap wr, DataType d_type, unsigned int mip_map_LOD)
{
	GLenum mg_filter;
	switch (mag_filter)
	{
	case Linear:
		mg_filter = GL_LINEAR;
		break;
	case Nearest:
		mg_filter = GL_NEAREST;
		break;
	case Nearest_Mipmap_Nearest:
		mg_filter = GL_NEAREST_MIPMAP_NEAREST;
		break;
	case Linear_mipmap_nearest:
		mg_filter = GL_LINEAR_MIPMAP_NEAREST;
		break;
	case Nearest_mipmap_linear:
		mg_filter = GL_NEAREST_MIPMAP_LINEAR;
		break;
	case Linear_mipmap_linear:
		mg_filter = GL_LINEAR_MIPMAP_LINEAR;
		break;
	default:
		break;
	}

	GLenum mn_filter;
	switch (min_filter)
	{
	case Linear:
		mn_filter = GL_LINEAR;
		break;
	case Nearest:
		mn_filter = GL_NEAREST;
		break;
	case Nearest_Mipmap_Nearest:
		mn_filter = GL_NEAREST_MIPMAP_NEAREST;
		break;
	case Linear_mipmap_nearest:
		mn_filter = GL_LINEAR_MIPMAP_NEAREST;
		break;
	case Nearest_mipmap_linear:
		mn_filter = GL_NEAREST_MIPMAP_LINEAR;
		break;
	case Linear_mipmap_linear:
		mn_filter = GL_LINEAR_MIPMAP_LINEAR;
		break;
	default:
		break;
	}

	GLenum wrap_s;
	switch (ws)
	{
	case Repeat:
		wrap_s = GL_REPEAT;
		break;
	case Mirrored_repeat:
		wrap_s = GL_MIRRORED_REPEAT;
		break;
	case Clamp_to_edge:
		wrap_s = GL_CLAMP_TO_EDGE;
		break;
	default:
		break;
	}

	GLenum wrap_t;
	switch (wt)
	{
	case Repeat:
		wrap_t = GL_REPEAT;
		break;
	case Mirrored_repeat:
		wrap_t = GL_MIRRORED_REPEAT;
		break;
	case Clamp_to_edge:
		wrap_t = GL_CLAMP_TO_EDGE;
		break;
	default:
		break;
	}

	GLenum wrap_r;
	switch (wr)
	{
	case Repeat:
		wrap_r = GL_REPEAT;
		break;
	case Mirrored_repeat:
		wrap_r = GL_MIRRORED_REPEAT;
		break;
	case Clamp_to_edge:
		wrap_r = GL_CLAMP_TO_EDGE;
		break;
	default:
		break;
	}

	GLenum f = GL_RGB;
	switch (format)
	{
	case R:
		f = GL_R;
		break;
	case RG:
		f = GL_RG;
		break;
	case RGB:
		f = GL_RGB;
		break;
	case RGBA:
		f = GL_RGBA;
		break;
	case Depth:
		f = GL_DEPTH_COMPONENT24;
	case Depth32:
		f = GL_DEPTH_COMPONENT32F;
		break;
	default:
		break;
	}

	GLenum type = GL_BYTE;
	switch (d_type) {
	case BYTE:
		type = GL_BYTE;
		break;
	case UNSIGNED_BYTE:
		type = GL_UNSIGNED_BYTE;
		break;
	case FLOAT:
		type = GL_FLOAT;
		break;
	case INT:
		type = GL_INT;
		break;
	case UNSIGNED_INT:
		type = GL_UNSIGNED_INT;
		break;
	case SHORT:
		type = GL_SHORT;
		break;
	case UNSIGNED_SHORT:
		type = GL_UNSIGNED_SHORT;
		break;
	}
	switch (type_)
	{
	case T_1D:
		glBindTexture(GL_TEXTURE_1D, id());

		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, mn_filter);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, mg_filter);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_R, wrap_r);

		glTexImage1D(GL_TEXTURE_1D, mip_map_LOD, f, width(), 0, format_, type, texture_.data());
		glGenerateMipmap(GL_TEXTURE_1D);
		break;
	case T_2D:
		glBindTexture(GL_TEXTURE_2D, id());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mn_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mg_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap_r);

		glTexImage2D(GL_TEXTURE_2D, mip_map_LOD, f, width(), height(), 0, format_, type, texture_.data());
		glGenerateMipmap(GL_TEXTURE_2D);
		break;
	case T_3D:
		glBindTexture(GL_TEXTURE_3D, id());

        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, mn_filter);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, mg_filter);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrap_r);

        glTexImage3D(GL_TEXTURE_3D, mip_map_LOD, f, width(), height(), depth(), 0, format_, type, texture_.data());
        glGenerateMipmap(GL_TEXTURE_3D);
        break;
	default:
		break;
	}
}
