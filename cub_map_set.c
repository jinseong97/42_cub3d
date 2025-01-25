/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:40:34 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:19:56 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_fc_color_set(int *fc, int *rgb)
{
	*fc |= rgb[0] << 16;
	*fc |= rgb[1] << 8;
	*fc |= rgb[2];
}

static void	dir_vec_set(t_game *game, int dx, int dy)
{
	game->vec->dir_x = dx;
	game->vec->dir_y = dy;
}

static void	plane_vec_set(t_game *game, int px, int py)
{
	game->vec->plane_x = px;
	game->vec->plane_y = py;
}

void	map_vec_value_set(t_game *game)
{
	if (game->map_info->player_news == 'N')
	{
		dir_vec_set(game, 0, -1);
		plane_vec_set(game, 1, 0);
	}
	else if (game->map_info->player_news == 'S')
	{
		dir_vec_set(game, 0, 1);
		plane_vec_set(game, -1, 0);
	}
	else if (game->map_info->player_news == 'E')
	{
		dir_vec_set(game, 1, 0);
		plane_vec_set(game, 0, 1);
	}
	else if (game->map_info->player_news == 'W')
	{
		dir_vec_set(game, -1, 0);
		plane_vec_set(game, 0, -1);
	}
}

void	map_set(t_game *game)
{
	map_fc_color_set(&game->floor->color, game->floor->rgb);
	map_fc_color_set(&game->ceiling->color, game->ceiling->rgb);
	map_vec_value_set(game);
	game->map_info->pos_x = game->map_info->player_x + 0.5;
	game->map_info->pos_y = game->map_info->player_y + 0.5;
	game->north->txtr = mlx_xpm_file_to_image(game->win->mlx, \
	game->north->file, &game->north->img_w, &game->north->img_h);
	game->south->txtr = mlx_xpm_file_to_image(game->win->mlx, \
	game->south->file, &game->south->img_w, &game->south->img_h);
	game->east->txtr = mlx_xpm_file_to_image(game->win->mlx, \
	game->east->file, &game->east->img_w, &game->east->img_h);
	game->west->txtr = mlx_xpm_file_to_image(game->win->mlx, \
	game->west->file, &game->west->img_w, &game->west->img_h);
	if (!game->north->txtr || !game->south->txtr || \
	!game->east->txtr || !game->west->txtr)
		print_error("Invalid txtr file!\n");
	game->north->addr = (unsigned int *)mlx_get_data_addr(game->north->txtr, \
	&game->north->bpp, &game->north->size_line, &game->north->endian);
	game->south->addr = (unsigned int *)mlx_get_data_addr(game->south->txtr, \
	&game->south->bpp, &game->south->size_line, &game->south->endian);
	game->east->addr = (unsigned int *)mlx_get_data_addr(game->east->txtr, \
	&game->east->bpp, &game->east->size_line, &game->east->endian);
	game->west->addr = (unsigned int *)mlx_get_data_addr(game->west->txtr, \
	&game->west->bpp, &game->west->size_line, &game->west->endian);
	game->win->win = mlx_new_window(game->win->mlx, WIN_WIDTH, WIN_HEIGHT, TI);
}
