#include <stdlib.h>
#include "utils/interop.h"

t_camera_data *convert_camera(t_camera *cam)
{
	t_camera_data	*cam_data;

	cam_data = malloc(sizeof(t_camera_data));
	if (!cam_data)
		return (NULL);
	cam_data->hfov = cam->fov;
	cam_data->eye = cam->viewpoint;
	cam_data->orientation = cam->orientation;
	cam_data->near = 1.0f;
	cam_data->far = 1000.0f;
	cam_data->image_h = IMG_HEIGHT;
	cam_data->image_w = IMG_WIDTH;
	return (cam_data);
}
