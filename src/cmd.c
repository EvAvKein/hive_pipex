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

t_cmd str_to_cmd(char *str)
{
	int		i;
	char	**split;

	if (!str)
		return ((t_cmd){.mergedc = 0, .argc = 0, .argv = NULL});
	split = ft_split(str, ' ');
	if (!split)
	{
		perrno("Command parsing", ENOMEM);
		return ((t_cmd){.mergedc = 0, .argc = 0, .argv = NULL});
	}
	i = 0;
	while (split[i])
		i++;
	if (!i)
	{
		free_str_arr(split);
		return ((t_cmd){.mergedc = 0, .argc = 0, .argv = NULL});
	}
	return ((t_cmd){.mergedc = i, .argc = i, .argv = split});	
}

static void exec(t_shell *shell, t_cmd *cmd, char *bin_path)
{
	char	*execve_prerror_s;

	execve(bin_path, cmd->argv, shell->envp);
	execve_prerror_s = ft_strjoin("pipex: ", bin_path);
	perror(execve_prerror_s);
	free(execve_prerror_s);
	free(bin_path);
	exit(1);
}

void run_cmd(t_shell *shell, t_cmd cmd, int dest_fd)
{
//	char		*bin_path;
	pid_t	pid;
	char	*bin_path;
	(void) dest_fd;

	// dup (2?) 0

	bin_path = path_to_binary(shell, cmd.argv[0]);
	if (!bin_path)
		bin_path = *cmd.argv;
	pid = fork();
	if (pid < 0)
		exit(!!ft_printf("ABANDON SHIP. ABANDON SHIP."));
	else if (!pid)
		exec(shell, &cmd, bin_path);
	else
		wait(0);
	free(bin_path);
}
