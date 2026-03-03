#include "core/color.h"

/*Crea un t_vec3 dai dati r g b*/

t_vec3 vec3_from_color(float r, float g, float b)
{
    return (vec3_new(r, g, b));
}