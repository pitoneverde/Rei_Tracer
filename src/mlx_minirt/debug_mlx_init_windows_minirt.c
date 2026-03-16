#include "minirt_renderer.h"
#include <string.h>
#include <stdio.h>

void	print_t_element(t_element *elem)
{
	if (!elem || !elem->id)
	{
		printf("NULL element\n");
		return ;
	}
	printf("Element id: %s\n", elem->id);
	if (strcmp(elem->id, "A") == 0)
	{
		printf("  Ambient Lighting:\n");
		printf("    brightness: %.2f\n", elem->value.a.brightness);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.a.color.rgba.red,
			elem->value.a.color.rgba.green,
			elem->value.a.color.rgba.blue);
	}
	else if (strcmp(elem->id, "C") == 0)
	{
		printf("  Camera:\n");
		printf("    viewpoint: (%.2f, %.2f, %.2f)\n",
			elem->value.c.viewpoint.x,
			elem->value.c.viewpoint.y,
			elem->value.c.viewpoint.z);
		printf("    orientation: (%.2f, %.2f, %.2f)\n",
			elem->value.c.orientation.x,
			elem->value.c.orientation.y,
			elem->value.c.orientation.z);
		printf("    FOV: %.2f\n", elem->value.c.fov);
	}
	else if (strcmp(elem->id, "L") == 0)
	{
		printf("  Light:\n");
		printf("    position: (%.2f, %.2f, %.2f)\n",
			elem->value.l.position.x,
			elem->value.l.position.y,
			elem->value.l.position.z);
		printf("    brightness: %.2f\n", elem->value.l.brightness);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.l.color.rgba.red,
			elem->value.l.color.rgba.green,
			elem->value.l.color.rgba.blue);
	}
	else if (strcmp(elem->id, "sp") == 0)
	{
		printf("  Sphere:\n");
		printf("    center: (%.2f, %.2f, %.2f)\n",
			elem->value.sp.center.x,
			elem->value.sp.center.y,
			elem->value.sp.center.z);
		printf("    diameter: %.2f\n", elem->value.sp.diameter);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.sp.color.rgba.red,
			elem->value.sp.color.rgba.green,
			elem->value.sp.color.rgba.blue);
	}
	else if (strcmp(elem->id, "pl") == 0)
	{
		printf("  Plane:\n");
		printf("    point: (%.2f, %.2f, %.2f)\n",
			elem->value.pl.point.x,
			elem->value.pl.point.y,
			elem->value.pl.point.z);
		printf("    normal: (%.2f, %.2f, %.2f)\n",
			elem->value.pl.normal.x,
			elem->value.pl.normal.y,
			elem->value.pl.normal.z);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.pl.color.rgba.red,
			elem->value.pl.color.rgba.green,
			elem->value.pl.color.rgba.blue);
	}
	else if (strcmp(elem->id, "cy") == 0)
	{
		printf("  Cylinder:\n");
		printf("    center: (%.2f, %.2f, %.2f)\n",
			elem->value.cy.center.x,
			elem->value.cy.center.y,
			elem->value.cy.center.z);
		printf("    axis: (%.2f, %.2f, %.2f)\n",
			elem->value.cy.axis.x,
			elem->value.cy.axis.y,
			elem->value.cy.axis.z);
		printf("    diameter: %.2f\n", elem->value.cy.diameter);
		printf("    height: %.2f\n", elem->value.cy.height);
		printf("    color: R=%u G=%u B=%u\n",
			elem->value.cy.color.rgba.red,
			elem->value.cy.color.rgba.green,
			elem->value.cy.color.rgba.blue);
	}
	else
	{
		printf("  Unknown element type\n");
	}
}

void print_t_element_array_sentinel(t_element *arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr->id)
    {
        printf("\n=== Element %d ===\n", i++);
        print_t_element(arr);
        arr++;
    }
}

void print_camera_data(const t_camera_data *cam)
{
	printf("CAMERA_DATA:\n");
	printf("hfov: %f\n", cam->hfov);
	printf("near: %f\n", cam->near);
	printf("far: %f\n", cam->far);
	printf("img_h: %d\n", cam->image_h);
	printf("img_w: %d\n", cam->image_w);
	vec3_print("eye", cam->eye);
	vec3_print("orientation", cam->orientation);
}

void print_cam(const t_camera_math *cam)
{
	printf("CAMERA_MATH:\n");
	mat4_print("cam_to_world", cam->cam_to_world);
	printf("hfov: %f\n", cam->hfov);
	printf("near: %f\n", cam->near_clip);
	printf("far: %f\n", cam->far_clip);
	printf("img_h: %d\n", cam->image_h);
	printf("img_w: %d\n", cam->image_w);
	printf("image_aspect: %f\n", cam->image_aspect);
	printf("zoom: %f\n", cam->zoom);
	printf("left:%f\n", cam->canvas[0]);
	printf("right:%f\n", cam->canvas[1]);
	printf("bottom:%f\n", cam->canvas[2]);
	printf("top:%f\n", cam->canvas[3]);
}
