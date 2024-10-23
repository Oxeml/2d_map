void	minimap_draw_line(t_mlx *mlx, float x_coord, float y_coord)
{
	printf("minimap draw line\n");
	int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;
	int width;
	int height;
	int that_x;
	int that_y;

	that_x = mlx->ply->coord_x;
	that_y = mlx->ply->coord_y;
	width = 64*(mlx->parse->rows + 1);
	height = 64*(mlx->parse->cols + 1);
    dx = ft_abs((int)x_coord - mlx->ply->coord_x);
    dy = ft_abs((int)y_coord - mlx->ply->coord_y);
    if (mlx->ply->coord_x < (int)x_coord)
        sx = 1;
    else
        sx = -1;
    if (mlx->ply->coord_y < (int)y_coord)
        sy = -1;
    else
        sy = 1;
    err = dx - dy;
    while (1)
	{
		if (that_x >= 0 && that_x < width
            && that_y >= 0 && that_y < height) //corrected width and height
			mlx_put_pixel(mlx->ray->minimap, that_x, that_y, 0x00FF00FF); //corrected img of minimap
		if (that_x == (int)x_coord
            && that_y == (int)y_coord)
			break;
        e2 = err * 2;
        if (e2 > -dy)
		{
            err -= dy;
            that_x += sx;
        }
        if (e2 < dx)
		{
            err += dx;
            that_y -= sy;
        }
    }
}

void put_block(t_mlx *mlx, int i, int j)
{
	//printf("put block\n");
	int		i_end;
	int		j_end;
	int		j_zero;

	j_zero = j;
	i_end = i + 64;
	j_end = j + 64;
	//printf("i_start: %d, i_end: %d, j_start: %d, j_end: %d, j_zero: %d\n", i, i_end, j, j_end, j_zero);
	while (i < i_end)
	{
		while (j < j_end)
		{
			//printf("coordinates to put pixel: [%d][%d]\n", i, j);
			mlx_put_pixel(mlx->ray->minimap, i, j, 0xFF00FFFF);
			j++;
		}
		j = j_zero;
		i++;
	}

}

void draw_vert (t_mlx *mlx)
{
	//printf("draw vert\n");
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 1;
	while (k < (mlx->parse->rows))
	{
		while (i < 64 * (mlx->parse->cols))
		{
			mlx_put_pixel(mlx->ray->minimap, 64*j, i, 0xFF00FFFF);
			i++;
		}
		i = 0;
		j++;
		k++;
	}
}

void draw_horiz (t_mlx *mlx)
{
	//printf("draw horiz\n");
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	j = 1;
	while (k < (mlx->parse->cols))
	{
		while (i < 64 * (mlx->parse->rows))
		{
			mlx_put_pixel(mlx->ray->minimap, i, 64 * j, 0xFF00FFFF);
			i++;
		}
		i = 0;
		j++;
		k++;
	}
}

void draw_player (t_mlx *mlx)
{
	//printf("draw player\n");
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x, mlx->ply->coord_y, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x + 1, mlx->ply->coord_y, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x + 2, mlx->ply->coord_y, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x - 1, mlx->ply->coord_y, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x - 2, mlx->ply->coord_y, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x, mlx->ply->coord_y + 1, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x, mlx->ply->coord_y - 1, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x, mlx->ply->coord_y + 2, 0x00FF00FF);
	mlx_put_pixel(mlx->ray->minimap, mlx->ply->coord_x, mlx->ply->coord_y - 2, 0x00FF00FF);
}

void draw_walls(t_mlx *mlx)
{
	// printf("draw walls\n");
	int		i;
	int		j;

	i = 0;
	while (i < mlx->parse->cols)
	{
		j = 0;
		while (j < mlx->parse->rows)
		{
			if (mlx->parse->map[i][j] == '1')
				put_block(mlx, j * 64, i * 64);
			j++;
		}
		j = 0;
		i++;
	}
}
void init_values(t_mlx *mlx)
{
	mlx->ply->map_i = mlx->ply->plyr_y; //indexes if the map array, column
	mlx->ply->map_j = mlx->ply->plyr_x; //index of the map line
	mlx->ply->coord_x = mlx->ply->map_i * TILE_SIZE + TILE_SIZE / 2; //DELETE //the pixel coordinate of the player
	mlx->ply->coord_y = mlx->ply->map_j * TILE_SIZE + TILE_SIZE / 2; //DELETE

	//for calculations of the ray
	mlx->ray->da = 0;
	mlx->ray->db = 0;
	mlx->ray->d_h = 0;
	mlx->ray->dist_hor_i = 0;
	mlx->ray->dist_vert_i = 0;
	mlx->ray->distance_to_wall = 0;
	mlx->ray->x1 = 0;
	mlx->ray->y1 = 0;
	mlx->ray->dtpp = 0;
	mlx->ray->wall_height = 0;
}

void	minimap_draw(t_mlx *mlx)
{
	//init_values(mlx);
	draw_walls(mlx);
	draw_vert(mlx);
	draw_horiz(mlx);
	draw_player(mlx);
	raycasting(mlx); //after drawing the grid
}