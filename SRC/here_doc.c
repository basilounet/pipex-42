/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:25:27 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/26 09:20:24 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	print_heredoc(t_px *px)
{
	int	i;

	i = -1;
	while (++i < px->total_cmd)
		ft_printf("pipe ");
	ft_printf("heredoc> ");
}

void	get_new_file(t_px *px, char *stop)
{
	char	*line;
	int		fd;

	if (!stop)
		error(px, MALLOC_ERROR);
	fd = open("heredoc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
		error(px, FILE_ERROR);
	print_heredoc(px);
	line = get_next_line(0);
	while (ft_strncmp(line, stop, ft_strlen(stop)))
	{
		ft_putstr_fd(line, fd);
		print_heredoc(px);
		free(line);
		line = get_next_line(0);
	}
	close(fd);
	free(stop);
	if (line)
		free(line);
}

void	remove_here_doc(t_px *px)
{
	char	**av;
	int		pid;

	av = ft_calloc(sizeof(char *), 4);
	if (!av)
		return ;
	av[0] = "/usr/bin/rm";
	av[1] = "-rf";
	av[2] = "heredoc";
	pid = fork();
	if (pid < 0)
		error(px, FORK_ERROR);
	if (pid == 0)
		execve(av[0], av, px->env);
	else
		wait(NULL);
	free(av);
}

void	here_doc(int ac, char **av, char **env)
{
	t_px	px;
	int		input_files[2];

	px = parse(ac - 1, av + 1, env);
	get_new_file(&px, ft_strjoin(av[2], "\n"));
	input_files[READ] = open("heredoc", O_RDONLY);
	input_files[WRITE] = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (input_files[READ] < 0 || input_files[WRITE] < 0)
		error(&px, FILE_ERROR);
	else if (ac == 5)
		sole_pipe(&px, input_files);
	else
		pipex(&px, input_files);
	remove_here_doc(&px);
	unleak(&px);
	exit(0);
}

//      here_doc stop ls sort "grep i" out_file