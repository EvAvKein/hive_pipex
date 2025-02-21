/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:15:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/21 21:15:25 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**str_to_argv(t_shell *shell, char *str)
{
	int		i;
	char	**split;

	if (!str)
		return (NULL);
	split = ft_split(str, ' ');
	if (!split)
		clean_exit(*shell, pipex_arg_errno("command parsing"));
	i = 0;
	while (split[i])
		i++;
	if (!i)
	{
		free_str_arr(split);
		clean_exit(*shell,
			(ft_dprintf(2, "pipex: %s: command not found", str) || 1));
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

void	process_cmd(t_shell *shell, t_cmd cmd, int *fds_close_until_negative)
{
	char	**cmd_argv;
	pid_t	pid;
	char	*bin_path;

	pid = fork();
	if (pid < 0 && (close(cmd.out_fd) || 1))
		clean_exit(*shell, pipex_arg_errno(cmd.str));
	if (pid && ++shell->waits)
		return ;
	if (cmd_is_empty_or_dir(cmd.str)
		&& ((close_both_unless_pipe(shell, cmd.in_fd, cmd.out_fd)
				&& pipex_arg_errno(shell->argv[shell->argc - 1])) || 1))
		clean_exit(*shell, 1);
	if (dup2(cmd.in_fd, STDIN_FILENO) < 0 || dup2(cmd.out_fd, STDOUT_FILENO) < 0
		|| if_either(
			close_both_unless_pipe(shell, cmd.in_fd, cmd.out_fd),
			close_until_negative(fds_close_until_negative)))
		clean_exit(*shell, pipex_arg_errno(cmd.str));
	cmd_argv = str_to_argv(shell, cmd.str);
	if ((!cmd_argv[0]) && free_str_arr(cmd_argv))
		clean_exit(*shell, (ft_dprintf(STDERR_FILENO,
					"pipex: %s: command not found") || 1));
	exec(shell, cmd_argv, path_to_binary(shell, cmd_argv[0]));
}
