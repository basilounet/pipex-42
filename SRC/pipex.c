/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:32:37 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/23 17:55:02 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int ac, char **av, char **env)
{
	t_px	px;
	int		input_files[2];

	if (ac > 1 && !ft_strncmp(av[1], "here_doc", 8))
		here_doc(ac, av, env);
	px = parse(ac, av, env);
	input_files[READ] = open(av[1], O_RDONLY);
	input_files[WRITE] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_files[READ] < 0 || input_files[WRITE] < 0)
		error(&px, FILE_ERROR);
	else if (ac == 4)
		sole_pipe(&px, input_files);
	else
		pipex(&px, input_files);
	unleak(&px);
}