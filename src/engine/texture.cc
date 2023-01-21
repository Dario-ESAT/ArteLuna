#include "..\..\include\engine\texture.h"
#include "comon_defs.h"
#include <glad/gl.h>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture() {
	width_ = 0;
	height_ = 0;
	depth_ = 0;
	min_filter_ = Linear;
	mag_filter_ = Linear;
	type_ = T_2D;
}

Texture::Texture(int d, Filter mag_filter, Filter min_filter, Type type, char* texture_src, Wrap ws, Wrap wt, Wrap wr )
{
	//width_ = w;
	//height_ = h;
	depth_ = d;
	min_filter_ = min_filter;
	mag_filter_ = mag_filter;
	wrap_s_ = ws;
	wrap_t_ = wt;
	wrap_r_ = wr;
	texture_ = stbi_load(texture_src, &width_, &height_, &channels_, 0);
	//texture_ = texture_data;
	switch (channels_) {
	case 1:
		format_ = R;
		break;
	case 2:
		format_ = RG;
		break;
	case 3:
		format_ = RGB;
		break;
	case 4:
		format_ = RGBA;
		break;
	}
	type_ = type;
	//if (id() != 0)
	glGenTextures(1, &id_texture_);
	glBindTexture(GL_TEXTURE_2D, id());
	glActiveTexture(GL_TEXTURE0);
}



Texture::~Texture() {

}

void Texture::set_texture(char* texture_src, int d, Filter mag_filter, Filter min_filter, Format format, Type type)
{
	texture_ = stbi_load(texture_src, &width_, &height_, &channels_, 0);
	min_filter_ = min_filter;
	mag_filter_ = mag_filter;
	type_ = type;
	depth_ = d;

	switch (channels_) {
	case 1:
		format_ = R;
		break;
	case 2:
		format_ = RG;
		break;
	case 3:
		format_ = RGB;
		break;
	case 4:
		format_ = RGBA;
		break;
	}
	
	//if (id() != 0)
	glGenTextures(1, &id_texture_);
	glBindTexture(GL_TEXTURE_2D, id());
	glActiveTexture(GL_TEXTURE0 + id());
}

void Texture::Bind()
{
	try {
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

void Texture::SetData(/*Filter mag_filter, Filter min_filter, Format format, */DataType d_type, unsigned int mip_map_LOD)
{
	GLenum mg_filter;
	switch (mag_filter_)
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
		throw 79;
	}

	GLenum mn_filter;
	switch (min_filter_)
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
		throw 80;
	}

	GLenum wrap_s;
	switch (wrap_s_)
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
		throw 81;
	}

	GLenum wrap_t;
	switch (wrap_t_)
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
		throw 82;
	}

	GLenum wrap_r;
	switch (wrap_r_)
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
		throw 83;
	}

	GLenum f = GL_RGB;
	switch (format_)
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
		throw 84;
	}

	GLenum type;
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
	default:
		throw 85;
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

		glTexImage1D(GL_TEXTURE_1D, mip_map_LOD, f, width(), 0, format_, type, texture_);
		glGenerateMipmap(GL_TEXTURE_1D);
		break;
	case T_2D:
		glBindTexture(GL_TEXTURE_2D, id());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mn_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mg_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, wrap_r);

		if (texture_) {
			glTexImage2D(GL_TEXTURE_2D, mip_map_LOD, f, width(), height(), 0, f, type, texture_);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			printf("Error loading the texture");
		}
		break;
	case T_3D:
		glBindTexture(GL_TEXTURE_3D, id());

        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, mn_filter);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, mg_filter);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, wrap_s);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, wrap_t);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, wrap_r);

        glTexImage3D(GL_TEXTURE_3D, mip_map_LOD, f, width(), height(), depth(), 0, format_, type, texture_);
        glGenerateMipmap(GL_TEXTURE_3D);
        break;
	default:
		throw 86;
	}
	stbi_image_free(texture_);
}
