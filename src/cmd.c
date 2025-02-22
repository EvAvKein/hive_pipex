/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:15:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 19:35:00by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	pipex_arg_errno("hmmm");//cmd_argv[0]);
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
	if (cmd_is_empty_or_dir(cmd))
		clean_exit(*shell, pipex_arg_errno(shell->argv[shell->argc - 1]));
	if (dup2(shell->prev_read, STDIN_FILENO) < 0
		|| dup2(shell->pipe_write, STDOUT_FILENO) < 0)
		clean_exit(*shell, pipex_arg_errno("huhhh"));//cmd));
	if (close_until_negative((int [4]){shell->prev_read, shell->pipe_write,
		shell->pipe_read, -1}))
		clean_exit(*shell, pipex_arg_errno(cmd));
	cmd_argv = str_to_argv(shell, cmd);
	if (!cmd_argv || (!cmd_argv[0] && free_str_arr(cmd_argv)))
		clean_exit(*shell, (ft_dprintf(STDERR_FILENO,
					"pipex: %s: command not found\n") || 1));
	exec(shell, cmd_argv, path_to_binary(shell, cmd_argv[0]));
}
