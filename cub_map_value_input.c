/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_map_value_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:32:41 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:39:39 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_news_input(char *line, char **news, int *flag)
{
	int	i;
	int	len;

	i = 0;
	if (line[i + 2] != ' ')
		print_error("Invalid map file!\n");
	i += 3;
	*news = ft_strdup(line + i);
	txtr_filename_check(*news);
	len = ft_strlen(*news);
	(*news)[len - 1] = 0;
	*flag = 1;
}

void	map_fc_input(char *line, int **fc, int *flag, int i)
{
	char	**tmp;
	int		k;

	k = 0;
	if (line[i++] != ' ')
		print_error("Invalid map file!\n");
	line[ft_strlen(line) - 1] = 0;
	tmp = ft_split(line + i, ',');
	while (tmp[k])
		k++;
	if (k != 3)
		print_error("Invalid map file!\n");
	k = 0;
	while (tmp[k])
	{
		(*fc)[k] = cub_atoi(tmp[k]);
		if ((*fc)[k] == -1)
			print_error("Invalid FC value!\n");
		k++;
	}
	k = 0;
	while (tmp[k])
		free(tmp[k++]);
	free(tmp);
	*flag = 1;
}
