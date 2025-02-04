/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:28:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/04 12:15:27 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// NAIVE IMPLEMENTATION, ACCOUNT FOR SUBSEQUENT CHARACTERS?
bool is_operator(char *arg)
{
	return (arg && (*arg  == '|' || *arg  == '<' || *arg  == '>'));
}
void *free_ptr_arr(void **vector, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(vector[i++]);
	free(vector);
	return (NULL);
}
