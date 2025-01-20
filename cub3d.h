/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:52:12 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/20 14:59:26 by jinsecho         ###   ########.fr       */
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

typedef struct s_flag
{
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		F;
	int		C;
}	t_flag;
typedef struct s_win
{
	void	*mlx;
	void	*win;
}	t_win;

typedef struct s_game
{
	char 			**map;
	char			*linecat;
	char			*NO;
	char			*SO;
	char			*WE;
	char			*EA;
	int				*F;
	int				*C;
	struct s_map	*map_info;
	struct s_win	mlx;
}	t_game;
typedef struct s_map
{
	int		w;
	int		h;
	char	player_news;
	int		player_x;
	int		player_y;
}	t_map;

#endif