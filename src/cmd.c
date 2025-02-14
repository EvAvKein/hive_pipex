/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:15:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/14 08:35:02 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**str_to_argv(char *str)
{
	int		i;
	char	**split;

	if (!str)
		return (NULL);
	split = ft_split(str, ' ');
	if (!split)
	{
		pipex_arg_errno("command parsing");
		return (NULL);
	}
	i = 0;
	while (split[i])
		i++;
	if (!i)
	{
		free_str_arr(split);
		return (NULL);
	}
	return (split);
}

static void	exec(t_shell *shell, char **cmd, char *bin_path)
{
	char	*errstring;

	execve(bin_path, cmd, shell->envp);
	errstring = strerror(errno);
	pipex_arg_errno(cmd[0]);
	if (cmd)
		free_str_arr(cmd);
	free(bin_path);
	clean_exit(*shell, 1);
}

void	process_cmd(t_shell *shell, t_cmd cmd, int child_close_fd)
{
	char	**cmd_argv;
	pid_t	pid;
	char	*bin_path;

	pid = fork();
	if (pid < 0)
		clean_exit(*shell, !!pipex_arg_errno(cmd.str));
	if (pid)
		return ;
	if (dup2(cmd.in_fd, STDIN_FILENO) < 0
		|| dup2(cmd.out_fd, STDOUT_FILENO) < 0)
		clean_exit(*shell, !!pipex_arg_errno(cmd.str));
	if (if_either(close(cmd.in_fd),
			if_either(close(cmd.out_fd), close(child_close_fd))))
		clean_exit(*shell, !!pipex_arg_errno(cmd.str));
	cmd_argv = str_to_argv(cmd.str);
	if (!cmd_argv)
		clean_exit(*shell, !!pipex_arg_errno("command parsing"));
	bin_path = path_to_binary(shell, cmd_argv[0]);
	if (!bin_path)
		bin_path = cmd_argv[0];
	exec(shell, cmd_argv, bin_path);
}

bool	run_first_cmd(t_shell *shell)
{
	int	infile;

	infile = open(shell->argv[1], O_RDONLY);
	if (infile < 0)
		return (!pipex_arg_errno(shell->argv[1]));
	process_cmd(shell, (t_cmd){.in_fd = infile, .out_fd = shell->outpipe_write,
		.str = shell->argv[2]}, shell->outpipe_read);
	if (close(infile))
		return (!pipex_arg_errno(shell->argv[1]));
	return (1);
}

bool	run_last_cmd_and_wait_all(t_shell *shell)
{
	int	outfile;
	int	cmd_count;

	cmd_count = shell->argc - 3;
	outfile = open(shell->argv[cmd_count + 2], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (outfile < 0)
		return (!pipex_arg_errno(shell->argv[cmd_count + 2]));
	process_cmd(shell, (t_cmd){.in_fd = shell->outpipe_read, .out_fd = outfile,
		.str = shell->argv[cmd_count + 1]}, shell->outpipe_write);
	if (if_either(close(shell->outpipe_read), close(shell->outpipe_write)))
		return (!pipex_arg_errno("pipe closing"));
	while (cmd_count--)
		wait(NULL);
	if (close(outfile))
		return (!pipex_arg_errno(shell->argv[shell->argc - 1]));
	return (1);
}
