#include "core/color.h"

/*trasforma srgb in lineare per altri calcoli*/
t_vec3 vec3_srgb_to_linear(t_vec3 srgb_color)
{
    t_vec3 linear;

    if (srgb_color.x <= 0.04045f)
        linear.x = srgb_color.x / 12.92f;
    else
        linear.x = powf((srgb_color.x + 0.055f) / 1.055f, 2.4f);
    if (srgb_color.y <= 0.04045f)
        linear.y = srgb_color.y / 12.92f;
    else
        linear.y = powf((srgb_color.y + 0.055f) / 1.055f, 2.4f);
    if (srgb_color.z <= 0.04045f)
        linear.z = srgb_color.z / 12.92f;
    else
        linear.z = powf((srgb_color.z + 0.055f) / 1.055f, 2.4f);
    return (linear);
}