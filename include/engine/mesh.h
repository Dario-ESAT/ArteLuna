#include "comon_defs.h"

class Mesh
{
public:
    Mesh();
    ~Mesh();
    //hacerlo unique o shared pointer
    Vtx* mesh_;
    int* indices_;
};
