/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:43:11 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 19:44:51 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	key_press_ws_print(t_game *game, int x, int y, char key)
{
	if (game->map[(int)game->map_info->pos_y][x] != '1')
	{
		if (key == 'w')
			game->map_info->pos_x += game->vec->dir_x * MOV_SET;
		else if (key == 's')
			game->map_info->pos_x -= game->vec->dir_x * MOV_SET;
	}
	if (game->map[y][(int)game->map_info->pos_x] != '1')
	{
		if (key == 'w')
			game->map_info->pos_y += game->vec->dir_y * MOV_SET;
		else if (key == 's')
			game->map_info->pos_y -= game->vec->dir_y * MOV_SET;
	}
	mlx_destroy_image(game->win->mlx, game->win->img);
	map_print(game);
}

static void	key_press_da_print(t_game *game, int x, int y, char key)
{
	if (game->map[(int)game->map_info->pos_y][x] != '1')
	{
		if (key == 'd')
			game->map_info->pos_x += game->vec->plane_x * MOV_SET;
		else if (key == 'a')
			game->map_info->pos_x -= game->vec->plane_x * MOV_SET;
	}
	if (game->map[y][(int)game->map_info->pos_x] != '1')
	{
		if (key == 'd')
			game->map_info->pos_y += game->vec->plane_y * MOV_SET;
		else if (key == 'a')
			game->map_info->pos_y -= game->vec->plane_y * MOV_SET;
	}
	mlx_destroy_image(game->win->mlx, game->win->img);
	map_print(game);
}

static void	key_press_arr_print(t_game *game, int pm)
{
	double	x_tmp;
	double	rot_tmp;

	rot_tmp = ROT_SET * pm;
	x_tmp = game->vec->dir_x;
	game->vec->dir_x = cos(rot_tmp) * game->vec->dir_x - \
	sin(rot_tmp) * game->vec->dir_y;
	game->vec->dir_y = sin(rot_tmp) * x_tmp + \
	cos(rot_tmp) * game->vec->dir_y;
	x_tmp = game->vec->plane_x;
	game->vec->plane_x = cos(rot_tmp) * game->vec->plane_x - \
	sin(rot_tmp) * game->vec->plane_y;
	game->vec->plane_y = sin(rot_tmp) * x_tmp + \
	cos(rot_tmp) * game->vec->plane_y;
	mlx_destroy_image(game->win->mlx, game->win->img);
	map_print(game);
}

int	key_press(int keycode, t_game *game)
{
	double	pos_x;
	double	pos_y;

	pos_x = game->map_info->pos_x;
	pos_y = game->map_info->pos_y;
	if (keycode == KEY_ESC)
		exit (EXIT_SUCCESS);
	if (keycode == KEY_W)
		key_press_ws_print(game, pos_x + game->vec->dir_x * MOV_SET, \
		pos_y + game->vec->dir_y * MOV_SET, 'w');
	else if (keycode == KEY_S)
		key_press_ws_print(game, pos_x - game->vec->dir_x * MOV_SET, \
		pos_y - game->vec->dir_y * MOV_SET, 's');
	else if (keycode == KEY_D)
		key_press_da_print(game, pos_x + game->vec->plane_x * MOV_SET, \
		pos_y + game->vec->plane_y * MOV_SET, 'd');
	else if (keycode == KEY_A)
		key_press_da_print(game, pos_x - game->vec->plane_x * MOV_SET, \
		pos_y - game->vec->plane_y * MOV_SET, 'a');
	else if (keycode == ARR_R)
		key_press_arr_print(game, 1);
	else if (keycode == ARR_L)
		key_press_arr_print(game, -1);
	return (0);
}

void	hook_setting(t_game *game)
{
	mlx_hook(game->win->win, 2, 1L << 0, &key_press, game);
	mlx_hook(game->win->win, 17, 0, game_close, game);
}
