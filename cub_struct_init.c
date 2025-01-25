/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_struct_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:34:43 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:13:27 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	news_struct_init(t_news **news)
{
	*news = (t_news *)malloc(sizeof(t_news));
	if (*news == NULL)
		exit (EXIT_FAILURE);
	(*news)->file = NULL;
	(*news)->txtr = NULL;
	(*news)->addr = NULL;
}

static void	fc_struct_init(t_fc **fc)
{
	*fc = (t_fc *)malloc(sizeof(t_fc));
	if (*fc == NULL)
		exit (EXIT_FAILURE);
	(*fc)->rgb = (int *)malloc(sizeof(int) * 3);
	if ((*fc)->rgb == NULL)
		exit (EXIT_FAILURE);
	(*fc)->color = 0;
}

void	game_struct_init(t_game *game)
{
	game->map = NULL;
	game->map_info = (t_map *)malloc(sizeof(t_map));
	if (game->map_info == NULL)
		exit (EXIT_FAILURE);
	game->vec = (t_vec *)malloc(sizeof(t_vec));
	if (game->vec == NULL)
		exit (EXIT_FAILURE);
	game->map_info->h = 0;
	game->map_info->w = 0;
	news_struct_init(&game->north);
	news_struct_init(&game->south);
	news_struct_init(&game->east);
	news_struct_init(&game->west);
	fc_struct_init(&game->floor);
	fc_struct_init(&game->ceiling);
}
