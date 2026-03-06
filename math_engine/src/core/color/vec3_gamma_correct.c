#include "core/color.h"

/*applica una correzione gamma outpot = input^(1/gamma), Il valore tipico di gamma è 2.2*/

t_vec3 vec3_gamma_correct(t_vec3 color, float gamma)
{
    t_vec3 result;
    float inv_gamma;

    inv_gamma = 1.0f / gamma;
    result.x = powf(color.x, inv_gamma);
    result.y = powf(color.y, inv_gamma);
    result.z = powf(color.z, inv_gamma);
    return (result);
}
