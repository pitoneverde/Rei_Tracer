#include "core/color.h"

/*converte il lineare a srgb*/

t_vec3 vec3_linear_to_srgb(t_vec3 linear_color)
{
    t_vec3 srgb;

    if (linear_color.x <= 0.0031308f)
        srgb.x = linear_color.x * 12.92f;
    else
        srgb.x = 1.055f * powf(linear_color.x, 1.0f / 2.4f) - 0.055f;
    if (linear_color.y <= 0.0031308f)
        srgb.y = linear_color.y * 12.92f;
    else
        srgb.y = 1.055f * powf(linear_color.y, 1.0f / 2.4f) - 0.055f;
    if (linear_color.z <= 0.0031308f)
        srgb.z = linear_color.z * 12.92f;
    else
        srgb.z = 1.055f * powf(linear_color.z, 1.0f / 2.4f) - 0.055f;
    return (srgb);
}
