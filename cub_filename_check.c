/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_filename_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 20:27:09 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:36:28 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	txtr_filename_check(char *filename)
{
	char	*ptr;

	ptr = ft_strnstr(filename, ".xpm\n", ft_strlen(filename));
	if (ptr == NULL)
		print_error("Invid_txtr_input\n");
	if (ft_strlen(ptr) != 5)
		print_error("Invid_txtr_input\n");
}

void	map_filename_check(char *filename)
{
	char	*ptr;

	ptr = ft_strnstr(filename, ".cub", ft_strlen(filename));
	if (ptr == NULL)
		print_error("filename Error!\n");
	if (ft_strlen(ptr) != 4)
		print_error("filename Error!\n");
}
