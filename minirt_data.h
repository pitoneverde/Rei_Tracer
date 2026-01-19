#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H 1
#include <stdint.h>

typedef union u_rgb
{
	struct
	{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;	//unused just to pad
	} t_color;
	uint32_t hex;
} t_rgb;

typedef struct s_point_3d
{
	float x;
	float y;
	float z;
} t_point_3d;

// Normalized 3D vector, range [-1,1] foreach direction
typedef struct s_vector_3d
{
	float dx;
	float dy;
	float dz;
} t_vector_3d;


// Data record of the .rt file
typedef struct
{
	char *id;
	union
	{
		struct
		{
			float brightness;	//[0.0,1.0]
			t_rgb color;
		} t_ambient_lighting;
		struct
		{
			t_point_3d viewpoint;
			t_vector_3d orientation;
			uint8_t fov;	//[0,180]
		} t_camera;
		struct
		{
			t_point_3d position;
			float brightness;	//[0.0,1.0]
			t_rgb color;	//unused in mandatory
		} t_light;
		struct
		{
			t_point_3d center;
			float diameter;
			t_rgb color;
		} t_sphere;
		struct
		{
			t_point_3d point;
			t_vector_3d normal;
			t_rgb color;
		} t_plane;
		struct
		{
			t_point_3d center;
			t_vector_3d axis;
			float diameter;
			float height;
			t_rgb color;
		} t_cylinder;
	} value;
} t_element;

#endif