#include "core/color.h"

/*Uso lo standard Rec. 709 / sRGB (usato per HDTV e computer grafica moderna)*/

float vec3_luminance(t_vec3 color)
{
    const float r_weight = 0.2126f;
    const float g_weight = 0.7152f;
    const float b_weight = 0.0722f;

    return (color.x * r_weight + color.y * g_weight + color.z * b_weight);
}
