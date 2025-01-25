/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:36:39 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:35:16 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	element_check(int *h, int *w, t_game *game, int *flag)
{
	*w = 0;
	while (game->map[*h][*w])
	{
		if (ft_strchr("01NSEW ", game->map[*h][*w]) == NULL)
			print_error("Invalid map!\n");
		if (*flag == 0 && ft_strchr("NSEW", game->map[*h][*w]))
		{
			*flag = 1;
			game->map_info->player_news = game->map[*h][*w];
			game->map_info->player_x = *w;
			game->map_info->player_y = *h;
		}
		else if (*flag == 1 && ft_strchr("NSEW", game->map[*h][*w]))
			print_error("Invalid map!\n");
		(*w)++;
	}
}

void	map_char_check(t_game *game)
{
	int	h;
	int	w;
	int	flag;

	h = 0;
	w = 0;
	flag = 0;
	while (game->map[h])
	{
		element_check(&h, &w, game, &flag);
		if (game->map_info->w < w)
			game->map_info->w = w;
		h++;
	}
	game->map_info->h = h;
	if (flag == 0)
		print_error("Invalid map!\n");
}

void	map_make_rectangle(t_game *game)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * (game->map_info->h + 5));
	if (tmp == NULL)
		exit (EXIT_FAILURE);
	while (i < game->map_info->h)
	{
		tmp[i] = (char *)malloc(sizeof(char) * game->map_info->w + 5);
		if (tmp[i++] == NULL)
			exit (EXIT_FAILURE);
	}
	i = 0;
	while (game->map[i])
	{
		cub_strncpy(tmp[i], game->map[i], game->map_info->w);
		i++;
	}
	tmp[i] = NULL;
	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
	game->map = tmp;
}

void	map_surrounded_wall_check(t_game *game, char **tmp, char c)
{
	int	h;
	int	w;

	h = 0;
	while (tmp[h])
	{
		w = 0;
		while (tmp[h][w])
		{
			if (tmp[h][w] == c)
			{
				if (h == 0 || w == 0)
					print_error("map is surrounded by walls!\n");
				else if (h == game->map_info->h - 1 || tmp[h][w + 1] == 0)
					print_error("map is surrounded by walls!\n");
				else if (tmp[h][w - 1] == ' ' || tmp[h][w + 1] == ' ')
					print_error("map is surrounded by walls!\n");
				else if (tmp[h - 1][w] == ' ' || tmp[h + 1][w] == ' ')
					print_error("map is surrounded by walls!\n");
			}
			w++;
		}
		h++;
	}
}

void	map_check(t_game *game, char *filename)
{
	int	fd;

	map_filename_check(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("file open fail!\n");
	map_read(game, fd);
	map_char_check(game);
	map_make_rectangle(game);
	map_surrounded_wall_check(game, game->map, '0');
	map_surrounded_wall_check(game, game->map, game->map_info->player_news);
}
