/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:48:36 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/21 17:54:03 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

enum		e_errors
{
	MALLOC_ERROR = 1,
	INVALID_AC_AMOUNT = 2,
	PATH_NOT_FOUND = 3
};

typedef struct s_px
{
	char	**env;
    char    ***cmd;
}			t_px;

/*========== ERRORS ==========*/

void		error(t_px *px, enum e_errors name);

/*========== UNLEAK ==========*/

void		unleak(t_px *px);

/*========== STRUCT_INIT ==========*/

void		init_px(t_px *px);

/*========== STRUCT_INIT ==========*/

t_px		parse(int ac, char **av, char **env);

#endif