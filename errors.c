/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/21 15:58:08 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(t_px *px, enum e_errors name)
{
	unleak(px);
	write(2, "Error\n", 6);
	if (name == MALLOC_ERROR)
		write(2, "[ ! ERROR ! ] A malloc error occured\n", 37);
    else if (name == INVALID_AC_AMOUNT)
		write(2, "[ ! ERROR ! ] Incorrect numbers of arguments\n", 45);
	else if (name == PATH_NOT_FOUND)
		write(2, "[ ! ERROR ! ] The path was not found\n", 37);
    exit(name);
}
