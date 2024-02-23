/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:32:37 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/22 11:03:22 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	sole_pipe(t_px *px, int input_files[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		child(px, input_files, input_files);
	else
	{
		close(input_files[READ]);
		close(input_files[WRITE]);
		wait(NULL);
	}
}

void	first_pipe(t_px *px, int input_files[2], int new_pipe[2])
{
	int	pid;

	pipe(new_pipe);
	pid = fork();
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		child(px, input_files, new_pipe);
	else
	{
		close(input_files[READ]);
		close(new_pipe[WRITE]);
		px->index++;
		wait(NULL);
	}
}

void	last_pipe(t_px *px, int input_files[2], int new_pipe[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		child(px, new_pipe, input_files);
	else
	{
		close(input_files[WRITE]);
		close(new_pipe[READ]);
		wait(NULL);
	}
}

void	pipex(t_px *px, int input_files[2])
{
	int	new_pipe[2];
	int	old_pipe[2];
	int	pid;

	first_pipe(px, input_files, new_pipe);
	while (px->index < px->total_cmd - 1)
	{
		old_pipe[0] = new_pipe[0];
		old_pipe[1] = new_pipe[1];
		pipe(new_pipe);
		pid = fork();
		if (pid < 0)
			error(px, FORK_ERROR);
		if (pid == 0)
			child(px, old_pipe, new_pipe);
		else
		{
			parent(px, old_pipe, new_pipe);
		}
		px->index++;
	}
	last_pipe(px, input_files, new_pipe);
}

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
