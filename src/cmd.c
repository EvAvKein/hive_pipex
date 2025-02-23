/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:00:42 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/23 18:00:49 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	set_strchr_colon_and_strlen(char *str, char **strchr, int *storage)
{
	*strchr = ft_strchr(str, ':');
	if (*strchr)
		*storage = *strchr - str;
	else
		*storage = ft_strlen(str);
}

static char	*path_to_binary(t_shell *shell, char *bin)
{
	char		*paths;
	char		*next_colon;
	int			path_len;
	char		*file_path;
	const int	bin_len = ft_strlen(bin);

	paths = shell->bin_paths;
	if (!bin || !*bin)
		return (NULL);
	if (ft_strchr(bin, '/'))
		return (bin);
	while (paths && *paths)
	{
		set_strchr_colon_and_strlen(paths, &next_colon, &path_len);
		file_path = ft_calloc(path_len + bin_len + 2, sizeof(char));
		if (!file_path && pipex_arg_errno("binary lookup"))
			return (NULL);
		((char *)ft_memcpy(file_path, paths, path_len))[path_len] = '/';
		ft_memcpy(file_path + path_len + 1, bin, bin_len);
		if (!access(file_path, X_OK))
			return (file_path);
		free(file_path);
		paths += (path_len + !!next_colon);
	}
	return (NULL);
}

static char	**str_to_argv(t_shell *shell, char *str)
{
	char	**split;

	if (!str)
		return (NULL);
	split = ft_split(str, ' ');
	if (!split)
		clean_exit(*shell, pipex_arg_errno("command parsing"));
	if (!*split)
	{
		free_str_arr(split);
		ft_dprintf(2, "pipex: %s: command not found\n", str);
		clean_exit(*shell, 1);
	}
	return (split);
}

static void	exec(t_shell *shell, char **cmd_argv, char *bin_path)
{
	if (!bin_path)
		bin_path = cmd_argv[0];
	execve(bin_path, cmd_argv, shell->envp);
	pipex_arg_errno(cmd_argv[0]);
	if (cmd_argv[0] != bin_path)
		free(bin_path);
	free_str_arr(cmd_argv);
	clean_exit(*shell, 1);
}

void	process_cmd(t_shell *shell, char *cmd)
{
	char	**cmd_argv;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		clean_exit(*shell, pipex_arg_errno(cmd));
	if (pid && ++shell->waits)
		return ;
	if (dup2(shell->prev_read, STDIN_FILENO) < 0
		|| dup2(shell->pipe_write, STDOUT_FILENO) < 0)
		clean_exit(*shell, pipex_arg_errno(cmd));
	close_all(shell);
	cmd_argv = str_to_argv(shell, cmd);
	if (!cmd_argv || (!cmd_argv[0] && free_str_arr(cmd_argv)))
		clean_exit(*shell, (ft_dprintf(STDERR_FILENO,
					"pipex: %s: command not found\n") || 1));
	if (cmd_is_empty_or_dir(cmd_argv[0]) && free_str_arr(cmd_argv))
		clean_exit(*shell, 1);
	exec(shell, cmd_argv, path_to_binary(shell, cmd_argv[0]));
}
