#include "core/color.h"

t_vec3 vec3_from_color(float r, float g, float b)
{
    return (vec3_new(r, g, b));
}

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

t_vec3 vec3_saturate(t_vec3 color)
{
    t_vec3  result;

    if (color.x < 0.0f)
        result.x = 0.0f;
    else if (color.x > 1.0f)
        result.x = 1.0f;
    else
        result.x = color.x;
    if (color.y < 0.0f)
        result.y = 0.0f;
    else if (color.y > 1.0f)
        result.y = 1.0f;
    else
        result.y = color.y;
    if (color.z < 0.0f)
        result.z = 0.0f;
    else if (color.z > 1.0f)
        result.z = 1.0f;
    else
        result.z = color.z;
    return (result);
}

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

float vec3_luminance(t_vec3 color)
{
    const float r_weight = 0.2126f;
    const float g_weight = 0.7152f;
    const float b_weight = 0.0722f;

    return (color.x * r_weight + color.y * g_weight + color.z * b_weight);
}