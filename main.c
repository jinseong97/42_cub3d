/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:51:43 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/03 23:36:36 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *errorcode)
{
	printf("%s", errorcode);
	exit (EXIT_FAILURE);
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

static void	map_news_input(char *line, char **news, int *flag)
{
	int	i;
	int	len;

	i = 0;
	if (line[i + 2] != ' ')
		print_error("Invalid map file!\n");
	i += 3;
	*news = ft_strdup(line + i);
	len = ft_strlen(*news);
	(*news)[len - 1] = 0;
	*flag = 1;
}

static void	map_fc_input(char *line, int **fc, int *flag)
{
	char	**tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (line[i + 1] != ' ')
		print_error("Invalid map file!\n");
	i += 2;
	line[ft_strlen(line) - 1] = 0;
	tmp = ft_split(line + i, ',');
	while (tmp[k])
		k++;
	if (k != 3)
		print_error("Invalid map file!\n");
	k = 0;
	while (tmp[k])
	{
		(*fc)[k] = ft_atoi(tmp[k]);
		k++;
	}
	k = 0;
	while (tmp[k])
		free(tmp[k++]);
	free(tmp);
	*flag = 1;
}

static void	flag_var_init(t_flag *flag)
{
	flag->NO = 0;
	flag->SO = 0;
	flag->WE = 0;
	flag->EA = 0;
	flag->F = 0;
	flag->C = 0;
}

static void	map_read(t_game *game, int fd)
{
	t_flag	flag;
	char	*line;
	char	*linecat;
	int		i;

	flag_var_init(&flag);
	linecat = ft_strdup("");
	while (1)
	{
		i = 0;
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (flag.NO == 1 && flag.SO == 1 && flag.WE == 1 && \
			flag.EA == 1 && flag.F == 1 && flag.C == 1)
			break ;
		if (line[i] == '\n')
		{
			free (line);
			continue ;
		}
		else if (ft_isalpha(line[i]) && line[i] != '\n' && line[i])
		{
			if (ft_strncmp("NO", line, 2) == 0)
				map_news_input(line, &(game->NO), &(flag.NO));
			else if (ft_strncmp("SO", line, 2) == 0)
				map_news_input(line, &(game->SO), &(flag.SO));
			else if (ft_strncmp("WE", line, 2) == 0)
				map_news_input(line, &(game->WE), &(flag.WE));
			else if (ft_strncmp("EA", line, 2) == 0)
				map_news_input(line, &(game->EA), &(flag.EA));
			else if (ft_strncmp("F", line, 1) == 0)
				map_fc_input(line, &(game->F), &(flag.F));
			else if (ft_strncmp("C", line, 1) == 0)
				map_fc_input(line, &(game->C), &(flag.C));
			else
				print_error("Invalid map file!\n");
		}
		// else if (line[i] == ' ' || line[i] == '1')
		// 	print_error("Invalid map file!\n");
		else
			print_error("Invalid map file!\n");
		free(line);
	}
	while (line[i] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (1)
	{
		i = 0;
		if (line[i] == ' ' || line[i] == '1')
		{
			if (ft_strchr(line, '1'))
				linecat = ft_strjoin(linecat, line);
			else
				print_error("Invalid map file!\n");
		}
		else
			print_error("Invalid map file!\n");
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	game->linecat = linecat;
	game->map = ft_split(linecat, '\n');
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
			if (ft_strchr("01NSEW ", game->map[h][w]) == NULL)
				print_error("Invalid map!\n");
			if (flag == 0 && ft_strchr("NSEW", game->map[h][w]))
			{
				flag = 1;
				game->map_info->player_news = game->map[h][w];
				game->map_info->player_x = w;
				game->map_info->player_y = h;
			}
			else if (flag == 1 && ft_strchr("NSEW", game->map[h][w]))
				print_error("Invalid map!\n");
			w++;
		}
		if (game->map_info->w < w)
			game->map_info->w = w;
		h++;
	}
	game->map_info->h = h;
}

void	cub_strncpy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (i < ft_strlen(src))
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
		dst[i++] = ' ';
	dst[i] = 0;
}

static void	map_make_rectangle(t_game *game)
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

static void	map_surrounded_wall_check(t_game *game, char **tmp, char c)
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

	filename_check(filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		print_error("file open fail!\n");
	map_read(game, fd);
	map_char_check(game);
	map_make_rectangle(game);
	map_surrounded_wall_check(game, game->map, '0');
	map_surrounded_wall_check(game, game->map, game->map_info->player_news);
	int i = 0;
	while (game->map[i])
		printf("%s|\n", game->map[i++]);
}

void	game_var_init(t_game *game)
{
	game->map = NULL;
	game->NO = NULL;
	game->SO = NULL;
	game->WE = NULL;
	game->EA = NULL;
	game->F = (int *)malloc(sizeof(int) * 3);
	if (game->F == NULL)
		exit (EXIT_FAILURE);
	game->C = (int *)malloc(sizeof(int) * 3);
	if (game->C == NULL)
		exit (EXIT_FAILURE);
	game->map_info = (t_map *)malloc(sizeof(t_map));
	if (game->map_info == NULL)
		exit (EXIT_FAILURE);
	game->map_info->h = 0;
	game->map_info->w = 0;
}

void	all_free(t_game *game)
{
	int	i = 0;
	
	free(game->NO);
	free(game->SO);
	free(game->WE);
	free(game->EA);
	free(game->F);
	free(game->C);
	free(game->map_info);
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
	free(game->linecat);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		print_error("Invalid argument!\n");
	game_var_init(&game);
	map_check(&game, av[1]);
	// printf("success\n");
	all_free(&game);
	return (0);
}
