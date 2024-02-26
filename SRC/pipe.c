/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:54:18 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/26 08:03:07 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	sole_pipe(t_px *px, int input_files[2])
{
	int	pid;

	pid = fork();
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		child(px, input_files, input_files, input_files);
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
		child(px, input_files, new_pipe, input_files);
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
		child(px, new_pipe, input_files, input_files);
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
			child(px, old_pipe, new_pipe, input_files);
		else
		{
			parent(px, old_pipe, new_pipe);
		}
		px->index++;
	}
	last_pipe(px, input_files, new_pipe);
}
