#include "minirt_renderer.h"

int    create_ambient(t_ambient_math *math, t_ambient_data *al)
{
    if (!math)
        return (1);
    math->ratio = al->ratio;
    math->color = al->color;
    return (0);
}