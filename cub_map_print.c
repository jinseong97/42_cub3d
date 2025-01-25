/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:41:39 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:20:11 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_var_set(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->raydir_x = game->vec->dir_x + game->vec->plane_x * ray->camera_x;
	ray->raydir_y = game->vec->dir_y + game->vec->plane_y * ray->camera_x;
	ray->map_pos_x = (int)floor(game->map_info->pos_x);
	ray->map_pos_y = (int)floor(game->map_info->pos_y);
	ray->delta_dist_x = fabs(1 / ray->raydir_x);
	ray->delta_dist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
	ray->txtr_x = game->win->bpp / 8;
}

void	ray_var_set2(t_game *game, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = \
		(game->map_info->pos_x - ray->map_pos_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = \
		(ray->map_pos_x + 1.0 - game->map_info->pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = \
		(game->map_info->pos_y - ray->map_pos_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = \
		(ray->map_pos_y + 1.0 - game->map_info->pos_y) * ray->delta_dist_y;
	}
}

void	ray_hit_check(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_pos_x += ray->step_x;
			ray->side = X;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_pos_y += ray->step_y;
			ray->side = Y;
		}
		if (game->map[ray->map_pos_y][ray->map_pos_x] == '1')
			ray->hit = 1;
	}
}

void	ray_var_set3(t_game *game, t_ray *ray)
{
	if (ray->side == X)
		ray->perp_wall_dist = (ray->map_pos_x - game->map_info->pos_x + \
		(1 - ray->step_x) / 2) / ray->raydir_x;
	else if (ray->side == Y)
		ray->perp_wall_dist = (ray->map_pos_y - game->map_info->pos_y + \
		(1 - ray->step_y) / 2) / ray->raydir_y;
	ray->wall_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->side == X)
		ray->wall_x = \
		game->map_info->pos_y + ray->perp_wall_dist * ray->raydir_y;
	else if (ray->side == Y)
		ray->wall_x = \
		game->map_info->pos_x + ray->perp_wall_dist * ray->raydir_x;
}

void	map_print(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	game->win->img = mlx_new_image(game->win->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->win->addr = mlx_get_data_addr(game->win->img, \
	&(game->win->bpp), &(game->win->size_line), &(game->win->endian));
	while (x < WIN_WIDTH)
	{
		ray_var_set(game, &ray, x);
		ray_var_set2(game, &ray);
		ray_hit_check(game, &ray);
		ray_var_set3(game, &ray);
		map_news_img_draw(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(\
	game->win->mlx, game->win->win, game->win->img, 0, 0);
}
