/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:48:36 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/22 11:00:54 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ 0
# define WRITE 1

# include "libft/libft.h"
# include "sys/wait.h"

enum		e_errors
{
	MALLOC_ERROR = 1,
	INVALID_AC_AMOUNT = 2,
	PATH_NOT_FOUND = 3,
	FILE_ERROR = 4,
	FORK_ERROR = 5
};

typedef struct s_px
{
	char	**env;
	char	***cmd;
	int		index;
	int		total_cmd;
}			t_px;

/*========== ERRORS ==========*/

void		error(t_px *px, enum e_errors name);

/*========== UNLEAK ==========*/

void		unleak(t_px *px);

/*========== STRUCT_INIT ==========*/

void		init_px(t_px *px);

/*========== STRUCT_INIT ==========*/

t_px		parse(int ac, char **av, char **env);

/*========== FORKS ==========*/

void		child(t_px *px, int input_fd[2], int output_fd[2]);
void		parent(t_px *px, int old_pipe[2], int new_pipe[2]);

/*========== HERE_DOCS ==========*/

void		here_doc(int ac, char **av, char **env);

#endif