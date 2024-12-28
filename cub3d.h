/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:52:12 by jinsecho          #+#    #+#             */
/*   Updated: 2024/12/28 20:42:47 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_S		115
# define KEY_A		97
# define KEY_D		100
# define BLOCK		32

typedef struct s_game
{
	char 			**map;
	struct s_map	*map_info;	
}	t_game;
typedef struct s_map
{
	int	w;
	int	h;
}	t_map;

#endif