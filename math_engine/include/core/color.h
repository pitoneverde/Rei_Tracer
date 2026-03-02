#ifndef COLOR_H
# define COLOR_H

#include "vec3.h"
#include <math.h>

// colors
t_vec3 vec3_from_color(float r, float g, float b);
t_vec3 vec3_srgb_to_linear(t_vec3 srgb_color);
t_vec3 vec3_linear_to_srgb(t_vec3 linear_color);
t_vec3 vec3_saturate(t_vec3 color);           // Clamp to [0,1]
t_vec3 vec3_gamma_correct(t_vec3 color, float gamma);
float vec3_luminance(t_vec3 color);         // Grayscale conversion
// t_vec3 vec3_lerp_color(t_vec3 a, t_vec3 b, float t); // Better for colors?
                                                                                                                                                    
#endif