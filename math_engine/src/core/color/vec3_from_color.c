#include "core/color.h"
#include <stdint.h>
#include "minirt_types.h"

/*Crea un t_vec3 dai dati r g b*/

t_vec3 vec3_from_color(float r, float g, float b)
{
	return (vec3_new(r / 255.0f, g / 255.0f, b / 255.0f));
}

t_vec3 vec3_from_color_hex(uint32_t hex)
{
    t_rgb converter;          // Create an instance of the union
    converter.hex = hex;      // Assign the hex value

    // Extract the RGB components (each 0–255) and convert to float (0.0–1.0)
    float r = converter.rgba.red   / 255.0f;
    float g = converter.rgba.green / 255.0f;
    float b = converter.rgba.blue  / 255.0f;

    // Return a new t_vec3 (the alpha channel is ignored)
    return vec3_new(r, g, b);
}