/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 21:15:03 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/04 13:21:54 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char **dupe_argv(int argc, char **argv)
{
	size_t	i;
	char	**copy;
	char	*dupe;

	i = 0;
	copy = ft_calloc(argc + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	while (i < argc)
	{
		dupe = ft_strdup(argv[i]);
		if (!dupe)
			return (free_ptr_arr(copy, i));
		copy[i] = dupe;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char *path_to_binary(char *command)
{
	char **bin_dirs;
	
	if (!bin_dirs)
}

t_cmd args_to_cmd(int argc, char **argv)
{
	size_t	i;
	char	**args;

	i = 0;
	while (i < argc)
	{
		if (is_operator(argv[i]))
			break; // MINISHELL: ADD SPECIFIC ERRORS
		i++;
	}
	if (!i)
		return ((t_cmd){.mergedc = 0, .argc = 0, .argv = NULL});
	args = dupe_argv(i, argv);
	if (!args && perrno("Command-handling error", ENOMEM))
		return ((t_cmd){.mergedc = 0, .argc = 0, .argv = NULL});	
	return ((t_cmd){.mergedc = i, .argc = i, .argv = args});	
}

void run_cmd(int argc, char **argv, char **envp, int dest_fd)
{
	pid_t	pid;

	// dup (2?) 0
	
	pid = fork();
	if (pid < 0)
		exit(!ft_printf("ABANDON SHIP. ABANDON SHIP."));
	else if (!pid)
	{
		ft_printf("in child\n");
		execve();
	}
	else
	{	
		ft_printf("in parent\n");
	
	}
}