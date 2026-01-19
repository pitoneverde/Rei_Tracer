#include "minirt.h"
#include <math.h>

/*
 * Example mock of data array of t_element type:
 * t_element file_data = {
 * {id = "A", {brightness = 0.2, color = {255, 255, 255}}},
 * {id = "C", {viewpoint = {-50.0, 0.0, 20.0}, orientation = {0.0, 0.0, 1.0}, fov = 80}},
 * {id = "L", {position = {-40.0, 50.0, 0.0}, brightness = 0.6, color = {10, 0, 255}}},
 * {id = "sp", {center = {0.0, 0.0, 20.6}, diameter = 12.6, color = {10, 0, 255}}},
 * {id = "pl", {point = {0.0, 0.0, -10.0}, normal = {0.0, 1.0, 0.0}, color = {0, 0, 255}}},
 * {id = "cy", {center = {50.0, 0.0, 20.6}, axis = {0.0, 0.0, 1.0}, diameter = 14.2, height = 21.42, color = {10, 0, 255}}}
 * }
 * ==> file contains:
 * A 0.2 255,255,255
 * C -50.0,0,20 0,0,1 80
 * L -40.0,50.0,0.0 0.6 10,0,255
 * sp 0.0,0.0,20.6 12.6 10,0,255
 * pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,255
 * cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
 * 
 * Note: since t_element is a raw tagged union, each t_element contains always:
 * id AND ONE of the union's structs (once chosen).
 * Once the t_element is initialized, the union's struct can be read as another (but you get garbage data)
 * and modifying the struct if it's not the right type leads to data corruption, flagged by cc (maybe).
 * sizeof(t_element) returns 8 + sizeof(t_cylinder) cause it's the largest one.
*/

int main(int argc, char **argv)
{
	// printf("%ld", sizeof(t_color));
	if (argc > 2)
		PRINT_ERR("Invalid argument count: %d", argc);
	t_element	*data_file = {0};
	parse_input(argc, argv, data_file);
	data_file->id = "cy";
	t_cylinder *cy = (t_cylinder *)&data_file->value;
	cy->center = (t_point3){.x = 0.0, .y = 0.0, .z = 1.0};
	cy->axis = (t_vector3){.x = 0.0, .y = 0.0, .z = 1.0};
	cy->diameter = 14.2;
	cy->height = 21.42;
	cy->color = (t_rgb)(t_color){10, 0, 255, 0}; //parsing & manipulation
	cy->color = (t_rgb)(uint32_t)0x1000FF00;	//for math & minlibx pixel

	// if (data_file[0]->id == "cy")
    // init();
    // launch();
    // cleanup();
    return (0);
}
