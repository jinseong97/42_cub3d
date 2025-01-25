/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_print1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:44:03 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:19:52 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_var_set(t_ray *ray, t_draw *draw)
{
	ray->wall_y = 0;
	draw->pxl_start = -ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (draw->pxl_start < 0)
		draw->pxl_start = 0;
	if (draw->pxl_start == 0)
		ray->wall_y = ray->wall_height / 2 - WIN_HEIGHT / 2;
	draw->pxl_end = ray->wall_height / 2 + WIN_HEIGHT / 2;
	if (draw->pxl_end >= WIN_HEIGHT)
		draw->pxl_end = WIN_HEIGHT - 1;
	if (ray->wall_height < 0)
	{
		draw->pxl_start = 0;
		draw->pxl_end = WIN_HEIGHT - 1;
	}
}

void	map_draw_window(t_game *game, t_news *news, t_ray *ray, int x)
{
	t_draw	draw;
	int		i;

	i = 0;
	draw_var_set(ray, &draw);
	while (i < draw.pxl_start)
	{
		draw.img_addr = game->win->addr + (game->win->size_line * i++ + x * 4);
		*(unsigned int *)draw.img_addr = game->ceiling->color;
	}
	while (draw.pxl_start <= draw.pxl_end)
	{
		ray->txtr_y = (int)(news->img_h * ray->wall_y++ / ray->wall_height);
		draw.txtr_pxl = (news->size_line * ray->txtr_y + ray->txtr_x) / 4;
		draw.img_addr = game->win->addr + \
		(draw.pxl_start * game->win->size_line + x * 4);
		*(unsigned int *)draw.img_addr = (int)news->addr[draw.txtr_pxl];
		draw.pxl_start++;
	}
	i = draw.pxl_end + 1;
	while (i < WIN_HEIGHT)
	{
		draw.img_addr = game->win->addr + (game->win->size_line * i++ + x * 4);
		*(unsigned int *)draw.img_addr = game->floor->color;
	}
}

void	map_news_img_draw(t_game *game, t_ray *ray, int x)
{
	if (ray->side && (ray->map_pos_y - game->map_info->pos_y) <= 0)
	{
		ray->txtr_x *= (game->north->img_w * (ray->wall_x - (int)ray->wall_x));
		map_draw_window(game, game->north, ray, x);
	}
	else if (ray->side && (ray->map_pos_y - game->map_info->pos_y) > 0)
	{
		ray->txtr_x *= (game->south->img_w * (ray->wall_x - (int)ray->wall_x));
		ray->txtr_x = game->south->img_w * 4 - ray->txtr_x - 1;
		map_draw_window(game, game->south, ray, x);
	}
	else if (ray->side == 0 && (ray->map_pos_x - game->map_info->pos_x) > 0)
	{
		ray->txtr_x *= (game->east->img_w * (ray->wall_x - (int)ray->wall_x));
		map_draw_window(game, game->east, ray, x);
	}
	else if (ray->side == 0 && (ray->map_pos_x - game->map_info->pos_x) <= 0)
	{
		ray->txtr_x *= (game->west->img_w * (ray->wall_x - (int)ray->wall_x));
		ray->txtr_x = game->west->img_w * 4 - ray->txtr_x - 1;
		map_draw_window(game, game->west, ray, x);
	}
}
