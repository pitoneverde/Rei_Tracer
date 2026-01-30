void    mlx_init_windows_minirt(t_element *data_file)
{
	// cose assolutamente obbligatorie per mlx
	int width = 800;
	int height = 800;
	void	*mlx = mlx_init();
	void	*window = mlx_new_window(mlx, width, height, "MiniRT window");
	void	*img = mlx_new_image(mlx, width, height);
	int bit_per_pixel;
	int line_lenght;
	int endian;
	char	*addr = mlx_get_data_addr(img, &bit_per_pixel, &line_lenght, &endian);

	//altre cose assolutament obbligatorie per mlx
	mlx_put_image_to_window(mlx, win, img, 0, 0);
	mlx_hook(win, 17, 1 << 17, free_all_minirt, &data_file);
	mlx_key_hook(win, key_hook_minirt, &data_file);
	mlx_loop(img);
}
