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
	int	i;
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
			return (free_str_arr(copy, i));
		copy[i] = dupe;
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char *path_to_binary(char **envp, char *cmd)
{
	char path;

	if (!cmd || !*cmd)
		return (NULL);
	while (ft_strncmp(*envp, "PATH=", 5))
		envp++;
	if (!*envp)
		return ((void *) !perr("PLACEHOLDER ERR: PATH env not found\n"));
	ft_printf("%s\n", *envp);
	return (NULL);
}

t_cmd args_to_cmd(int argc, char **argv)
{
	int	i;
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
//	char		*bin_path;
	pid_t		pid;
//	(void) bin_path;
	(void) argc;
	(void) argv;
	(void) envp;
	(void) dest_fd;

	// dup (2?) 0

	// bin_path = path_to_binary();

	pid = fork();
	if (pid < 0)
		exit(!ft_printf("ABANDON SHIP. ABANDON SHIP."));
	else if (!pid)
	{
		ft_printf("in child\n");
		// execve();
	}
	else
	{	
		ft_printf("in parent\n");
		// waitpid();
	}
}