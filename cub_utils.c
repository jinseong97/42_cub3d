/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jakim <jakim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 22:14:16 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 17:08:11 by jakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error(char *errorcode)
{
	printf("Error\n%s", errorcode);
	exit (EXIT_FAILURE);
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

int	cub_atoi(char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if ('0' <= str[i] && str[i] <= '9')
	{
		while ('0' <= str[i] && str[i] <= '9')
		{
			num *= 10;
			num = num + (str[i] - '0');
			if (num > 255)
				return (-1);
			i++;
		}
		if (str[i] != 0)
			return (-1);
	}
	else
		return (-1);
	return (num);
}

void	all_free(t_game *game)
{
	int	i;

	i = 0;
	free(game->north->file);
	free(game->south->file);
	free(game->east->file);
	free(game->west->file);
	free(game->floor->rgb);
	free(game->ceiling->rgb);
	free(game->map_info);
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
}
