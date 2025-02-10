/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:23:31 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/10 15:46:30 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void set_strchr_colon_and_strlen(char *str, char **strchr, int *storage)
{
	*strchr = ft_strchr(str, ':');
	if (*strchr)
		*storage = *strchr - str;
	else
		*storage = ft_strlen(str);
	
}

char *path_to_binary(t_shell *shell, char *bin)
{
	char		*paths;
	char		*next_colon;
	int			path_len;
	char		*file_path;
	const int	bin_len = ft_strlen(bin);

	paths = shell->bin_paths;
	if (!paths || !*paths || !bin || !*bin)
		return (NULL); // HANDLE BETTER?
	if (ft_strchr(bin, '/'))
		return (ft_strdup(bin));
	while (*paths)
	{
		set_strchr_colon_and_strlen(paths, &next_colon, &path_len);
		file_path = ft_calloc(path_len + bin_len + 2, sizeof(char));
		if (!file_path)
			perrno("Binary lookup", ENOMEM);
		((char *)ft_memcpy(file_path, paths, path_len))[path_len] = '/';
		ft_memcpy(file_path + path_len + 1, bin, bin_len);
		if (!access(file_path, X_OK))
			return (file_path);
		free(file_path);
		paths += (path_len + !!next_colon);
	}
	return (NULL);
}
