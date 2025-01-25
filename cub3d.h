/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 17:52:12 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:36:57 by jinsecho         ###   ########.fr       */
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
# include <math.h>
# define TI			"cub3D"
# define KEY_ESC	65307
# define KEY_W		119
# define KEY_S		115
# define KEY_A		97
# define KEY_D		100
# define ARR_R		65363
# define ARR_L		65361
# define ROT_SET	0.04
# define MOV_SET	0.1333
# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define X			0
# define Y			1

typedef struct s_news
{
	char			*file;
	void			*txtr;
	unsigned int	*addr;
	int				bpp;
	int				endian;
	int				size_line;
	int				img_w;
	int				img_h;
}	t_news;
typedef struct s_fc
{
	int	*rgb;
	int	color;
}	t_fc;
typedef struct s_map
{
	int		w;
	int		h;
	char	player_news;
	double	player_x;
	double	player_y;
	double	pos_x;
	double	pos_y;
}	t_map;
typedef struct s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
}	t_win;
typedef struct s_pars
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}	t_pars;
typedef struct s_vec
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_vec;
typedef struct s_ray
{
	double	raydir_x;
	double	raydir_y;
	double	camera_x;
	int		map_pos_x;
	int		map_pos_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		wall_height;
	double	wall_x;
	int		wall_y;
	int		txtr_x;
	int		txtr_y;
}	t_ray;
typedef struct s_draw
{
	char	*img_addr;
	int		pxl_start;
	int		pxl_end;
	int		txtr_pxl;
}	t_draw;
typedef struct s_game
{
	char			**map;
	t_win			*win;
	struct s_map	*map_info;
	struct s_vec	*vec;
	struct s_news	*north;
	struct s_news	*south;
	struct s_news	*east;
	struct s_news	*west;
	struct s_fc		*floor;
	struct s_fc		*ceiling;
}	t_game;

int		game_close(void);

int		cub_atoi(char *str);
void	cub_strncpy(char *dst, char *src, int len);
void	print_error(char *errorcode);
void	all_free(t_game *game);

void	game_struct_init(t_game *game);
void	map_check(t_game *game, char *filename);
void	map_set(t_game *game);
void	txtr_filename_check(char *filename);
void	map_filename_check(char *filename);
void	map_news_input(char *line, char **news, int *flag);
void	map_fc_input(char *line, int **fc, int *flag, int i);

void	map_print(t_game *game);
void	map_news_img_draw(t_game *game, t_ray *ray, int x);
void	hook_setting(t_game *game);
void	map_read(t_game *game, int fd);

#endif
