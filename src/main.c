/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/10 20:59:17 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool init_shell(t_shell *shell)
{
	char	**env;

	env = shell->envp;
	while (ft_strncmp(*env, "PATH=", 5))
		env++;
	if (!*env)
		return (!perr("PLACEHOLDER ERR: PATH env not found\n"));
	if (!*(env + 5))
		return (!perr("PLACEHOLDER ERR: PATH env empty\n"));
	shell->bin_paths = (*env + 5);
	if (pipe(&shell->inpipe_read) || pipe(&shell->outpipe_read))
		return (!perr("Pipe failure\n"));
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;

	shell = (t_shell){
		.argc = argc,
		.argv = argv,
		.envp = envp,
		.bin_paths = NULL,
		.inpipe_read = -1,
		.inpipe_write = -1,
		.outpipe_read = -1,
		.outpipe_write = -1
	};
	if (!init_shell(&shell))
		return (1);
	pipex(shell, argc, argv);
	return (1);
}