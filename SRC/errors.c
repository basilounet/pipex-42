/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvasseur <bvasseur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 13:47:19 by bvasseur          #+#    #+#             */
/*   Updated: 2024/02/23 16:00:51 by bvasseur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error(t_px *px, enum e_errors name)
{
	write(2, "Error\n", 6);
	unleak(px);
	if (name == MALLOC_ERROR)
		write(2, "[ ! ERROR ! ] A malloc error occured\n", 37);
	else if (name == INVALID_AC_AMOUNT)
		write(2, "[ ! ERROR ! ] Incorrect numbers of arguments\n", 45);
	else if (name == PATH_NOT_FOUND)
		write(2, "[ ! ERROR ! ] The path was not found\n", 37);
	else if (name == FILE_ERROR)
		write(2, "[ ! ERROR ! ] An error occured with the files\n", 46);
	else if (name == FORK_ERROR)
		write(2, "[ ! ERROR ! ] The fork failed\n", 30);
	exit(name);
}
