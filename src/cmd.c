/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:15:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 14:47:22by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char **str_to_argv(char *str)
{
	int		i;
	char	**split;

	if (!str)
		return (NULL);
	split = ft_split(str, ' ');
	if (!split)
	{
		perrno("Command parsing", ENOMEM);
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
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s", bin_path, errstring);
	if (cmd)
		free_str_arr(cmd);
	free(errstring);
	free(bin_path);
	clean_exit(*shell, errno); // CODE FOR EXEC FAILURE?
}

void process_cmd(t_shell *shell, t_cmd cmd, int child_close_fd)
{
	char	**cmd_argv;
	pid_t	pid;
	char	*bin_path;
	
	//ft_printf("input %i, cmd %s, output %i\n", input_fd, cmd.argv[0], output_fd);
	pid = fork();
	if (pid < 0)
		clean_exit(*shell, errno + !perr("pipex: fork failure\n"));
	if (pid)
		return ;
	if (dup2(cmd.in_fd, STDIN_FILENO) < 0
		|| dup2(cmd.out_fd, STDOUT_FILENO) < 0)
		clean_exit(*shell, errno + !perr("pipex: dup2 failure\n"));
	close(cmd.in_fd);
	close(cmd.out_fd);
	close(child_close_fd);
	cmd_argv = str_to_argv(cmd.str);
	bin_path = path_to_binary(shell, cmd_argv[0]);
	if (!bin_path)
		bin_path = cmd_argv[0];
	exec(shell, cmd_argv, bin_path);
}
