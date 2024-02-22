/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:35:20 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/22 05:53:36 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_command(t_px *px, char *command, int index)
{
    char    **cmd;
	char	*str;
	int		i;

    i = 0;
    cmd = ft_split(command, ' ');
    if (!cmd)
        error(px, MALLOC_ERROR);
    while (px->env[i])
    {
        str = ft_strjoin3(px->env[i], "/", cmd[0]);
        if (!str)
            error(px, MALLOC_ERROR);
        if(!access(str, F_OK) && !access(str, X_OK))
        {
            free(cmd[0]);
            cmd[0] = str;
            px->cmd[index] = cmd;
            return ;
        }
        free(str);
        i++;
    }
    error(px, PATH_NOT_FOUND);
}

void	check_access(t_px *px, int ac, char **av)
{
    int i;

    i = -1;
    while (++i < ac)
        check_command(px, av[i], i);
    //ft_print_split_map(px->cmd);
}

t_px	parse(int ac, char **av, char **env)
{
	t_px	px;
	int		i;

	i = 0;
	init_px(&px);
	if (ac < 4)
		error(&px, INVALID_AC_AMOUNT);
	if (!env)
		error(&px, PATH_NOT_FOUND);
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		error(&px, PATH_NOT_FOUND);
	px.env = ft_split(env[i] + 5, ':');
	if (!px.env)
		error(&px, MALLOC_ERROR);
    px.total_cmd = ac - 3;
    px.cmd = ft_calloc(sizeof(char **), px.total_cmd + 1);
    if (!px.cmd)
        error(&px, MALLOC_ERROR);
    check_access(&px, ac - 3, av + 2);
	return (px);
}
