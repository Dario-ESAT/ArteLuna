Crear una textura y aplicarla a una entidad

Empezaremos por crear una textura y pasarle los parametros que nosotros queramos para esta.

Los parametros son:  Texture(int depth, Filter mag_filter, Filter min_filter, Type type, char* texture_src, Wrap wrap_s, Wrap wrap_t, Wrap wrap_r);
Para conocer los posibles parametros de Filter, Type o Wrap consultar el final del Readme

Una vez creada la textura deberemos llamar a su función SetData() antes del bucle con los siguientes parametros:

SetData(DataType d_type, unsigned int mip_map_LOD);
Para conocer los posibles parametros de DataType consultar el final del Readme.

Por último tan solo deberemos llamar a la función set_texture() de la textura dentro del bucle con los siguientes parametros:
set_texture(char* texture_src, Filter mag_filter, Filter min_filter, Format format, Type type);
Para conocer los posibles parametros de Filter, Format y Type consultar el final del Readme.


  Filter {
       	Linear,
        Nearest,
        Nearest_Mipmap_Nearest,
        Linear_mipmap_nearest,
        Nearest_mipmap_linear,
        Linear_mipmap_linear
    };

    DataType {
        BYTE,
        UNSIGNED_BYTE,
        FLOAT,
        INT,
        UNSIGNED_INT,
        SHORT,
        UNSIGNED_SHORT,
    };

    Wrap {
        Repeat,
        Mirrored_repeat,
        Clamp_to_edge,
    };

    Type {
        T_Invalid = 0,
        T_1D,
        T_2D,
        T_3D,
        T_Cubemap,
    };

    Format {
        None = 0,
        R,
        RG,
        RGB,
        RGBA,
        Depth,
        Depth32,
    };