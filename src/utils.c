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
void *free_str_arr(char **arr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

size_t	len_until_chr(char *str, char chr)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != chr)
		i++;
	return (i);
}