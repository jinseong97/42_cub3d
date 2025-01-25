/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:24:11 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:39:10 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_value_flag_init(t_pars *flag)
{
	flag->no = 0;
	flag->so = 0;
	flag->we = 0;
	flag->ea = 0;
	flag->f = 0;
	flag->c = 0;
}

static void	map_data_set(char **line, t_pars *flag, t_game *game)
{
	if (ft_strncmp("NO", *line, 2) == 0)
		map_news_input((*line), &(game->north->file), &(flag->no));
	else if (ft_strncmp("SO", (*line), 2) == 0)
		map_news_input((*line), &(game->south->file), &(flag->so));
	else if (ft_strncmp("EA", (*line), 2) == 0)
		map_news_input((*line), &(game->east->file), &(flag->ea));
	else if (ft_strncmp("WE", (*line), 2) == 0)
		map_news_input((*line), &(game->west->file), &(flag->we));
	else if (ft_strncmp("F", (*line), 1) == 0)
		map_fc_input((*line), &(game->floor->rgb), &(flag->f), 1);
	else if (ft_strncmp("C", (*line), 1) == 0)
		map_fc_input((*line), &(game->ceiling->rgb), &(flag->c), 1);
	else
		print_error("Invalid map file!\n");
}

static int	data_validate(int *i, char **line, t_game *game, t_pars *flag)
{
	*i = 0;
	if (*line == NULL)
		print_error("Invalid map file!\n");
	if (flag->no == 1 && flag->so == 1 && flag->we == 1 && \
		flag->ea == 1 && flag->f == 1 && flag->c == 1)
		return (1);
	if ((*line)[*i] == '\n')
	{
		free (*line);
		*line = NULL;
		return (0);
	}
	else if (ft_isalpha((*line)[*i]) && (*line)[*i] != '\n' && (*line)[*i])
		map_data_set(line, flag, game);
	else
		print_error("Invalid map file!\n");
	free(*line);
	(*line) = NULL;
	return (0);
}

static int	make_map(int *i, char **line, char **linecat, int fd)
{
	*i = 0;
	if ((*line)[*i] == ' ' || (*line)[*i] == '1')
	{
		if (ft_strchr((*line), '1'))
			*linecat = ft_strjoin(*linecat, (*line));
		else
			print_error("Invalid map file!\n");
	}
	else
		print_error("Invalid map file!\n");
	free(*line);
	(*line) = get_next_line(fd);
	if ((*line) == NULL)
		return (1);
	return (0);
}

void	map_read(t_game *game, int fd)
{
	t_pars	flag;
	char	*line;
	char	*linecat;
	int		i;

	map_value_flag_init(&flag);
	linecat = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (data_validate(&i, &line, game, &flag))
			break ;
	}
	while (line[i] == '\n')
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			print_error("Invalid map file!\n");
	}
	while (1)
		if (make_map(&i, &line, &linecat, fd))
			break ;
	game->map = ft_split(linecat, '\n');
	free(linecat);
}
