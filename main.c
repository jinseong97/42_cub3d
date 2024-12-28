/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:51:43 by jinsecho          #+#    #+#             */
/*   Updated: 2024/12/28 23:31:12 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *errorcode)
{
	printf("%s", errorcode);
	exit (1);
}

static void	filename_check(char *filename)
{
	char	*ptr;

	ptr = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (ptr == NULL)
		print_error("filename Error!\n");
	if (ft_strlen(ptr) != 4)
		print_error("filename Error!\n");
	
}

static void	map_read_cnt(t_game *game, int fd)
{
	char	*line;
	char	*line_cat;
	char	**line_idx;
	int		i;
	int		tmp_len = 0;

	line_cat = ft_strdup("");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (tmp_len == 0)
		{
			if (ft_strchr(line, '\n'))
				tmp_len = ft_strlen(line) - 1;
			else
				tmp_len = ft_strlen(line);
		}
		else
		{
			if (ft_strchr(line, '\n'))
			{
				if (tmp_len != ft_strlen(line) - 1)
					print_error ("Invalid map!\n");
			}
			else
				if (tmp_len != ft_strlen(line))
					print_error ("Invalid map!\n");
		}
		line_cat = ft_strjoin(line_cat, line);
		free(line);
	}
	line_idx = ft_split(line_cat, '\n');
	if (line_idx == NULL)
		exit (EXIT_FAILURE);
	free(line_cat);
	while (line_idx[++i]);
	game->map = line_idx;
	game->map_info->h = i;
	printf("%d", i);
	game->map_info->w = tmp_len;
}

static void	map_char_check(t_game *game)
{
	int	h = 0;
	int	w = 0;
	int	flag = 0;
	
	while (game->map[h])
	{
		w = 0;
		while (game->map[h][w])
		{
			if (ft_strchr("01NSEW", game->map[h][w]) == NULL)
				print_error("Invalid map!\n");
			if (flag == 0 && ft_strchr("NSEW", game->map[h][w]))
				flag = 1;
			else if (flag == 1 && ft_strchr("NSEW", game->map[h][w]))
				print_error("Invalid map!\n");
			w++;
		}
		h++;
	}
}

void	map_check(t_game *game, char *filename)
{
	int	fd;

	filename_check(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("file open fail!\n");
	map_read_cnt(game, fd);
	map_char_check(game);
}

void	game_var_init(t_game *game)
{
	game->map = NULL;
	game->map_info = (t_map *)malloc(sizeof(t_map));
	if (game->map_info == NULL)
		exit (EXIT_FAILURE);
	game->map_info->h = 0;
	game->map_info->w = 0;
}

void	all_free(t_game *game)
{
	free(game->map_info);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		print_error("Invalid argument!\n");
	game_var_init(&game);
	map_check(&game, av[1]);
	printf("success\n");
	all_free(&game);
	return (0);
}
