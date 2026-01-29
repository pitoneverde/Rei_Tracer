#ifndef MINIRT_DATA_H
# define MINIRT_DATA_H 1
#include "minirt_types.h"

typedef struct s_ambient_lighting
{
	float brightness;	//[0.0,1.0]
	t_rgb color;
} t_ambient_lighting;

typedef	struct s_camera
{
	t_point3 viewpoint;
	t_vector3 orientation;
	uint8_t fov;	//[0,180]
} t_camera;

typedef	struct s_light
{
	t_point3 position;
	float brightness;	//[0.0,1.0]
	t_rgb color;	//unused in mandatory
} t_light;

typedef struct s_sphere
{
	t_point3 center;
	float diameter;
	t_rgb color;
} t_sphere;

typedef struct s_plane
{
	t_point3 point;
	t_vector3 normal;
	t_rgb color;
} t_plane;

typedef struct s_cylinder
{
	t_point3 center;
	t_vector3 axis;
	float diameter;
	float height;
	t_rgb color;
} t_cylinder;

// Data record of the .rt file
// vec3 in t_element is a normalized 3D vector, range [-1,1] foreach direction
typedef struct s_element
{
	char *id;
	union
	{
		t_ambient_lighting a;
		t_camera c;
		t_light l;
		t_sphere sp;
		t_plane pl;
		t_cylinder cy;
	} value;
} t_element;

t_rgb rgb_new(uint8_t red, uint8_t green, uint8_t blue);
t_rgb rgb_from_hex(uint32_t hex);

#endif
