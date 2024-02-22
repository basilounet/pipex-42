/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 02:50:01 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/22 06:02:03 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    child(t_px *px, int input_fd[2], int output_fd[2])
{
    dup2(input_fd[READ], STDIN_FILENO);
    dup2(output_fd[WRITE], STDOUT_FILENO);
    close(input_fd[READ]);
    close(input_fd[WRITE]);
    close(output_fd[READ]);
    close(output_fd[WRITE]);
    execve(px->cmd[px->index][0], px->cmd[px->index], px->env);
}

void    parent(t_px *px, int old_pipe[2], int new_pipe[2])
{
    (void)px;
    close(new_pipe[WRITE]);
    //ft_printf("maybe here\n");
    wait(NULL);
    close(old_pipe[READ]);
}
