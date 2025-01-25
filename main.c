/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 23:31:45 by jinsecho          #+#    #+#             */
/*   Updated: 2025/01/25 20:27:39 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_close(void)
{
	exit (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_win	win;

	if (ac != 2)
		print_error("Invalid argument!\n");
	game.win = &win;
	game_struct_init(&game);
	map_check(&game, av[1]);
	game.win->mlx = mlx_init();
	map_set(&game);
	map_print(&game);
	hook_setting(&game);
	mlx_loop(game.win->mlx);
	all_free(&game);
	return (0);
}
