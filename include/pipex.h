/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 18:48:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft_full/libft_full.h"
# include "perrs.h"

typedef	struct	s_cmd
{
	int			mergedc;
	int			argc;
	char		**argv;
}					t_cmd;

typedef	struct	s_shell
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*bin_paths;
}					t_shell;

bool	init_bin_paths(t_shell *shell);

int		pipex(int argc, char **args, char **envp);
int		here_doc(char **args);

void	run_cmd(t_shell *shell, t_cmd cmd, int dest_fd);
t_cmd	str_to_cmd(char *arg);

char	*path_to_binary(t_shell *shell, char *bin);

bool	is_operator(char *arg);
bool	free_str_arr(char **arr);
size_t	len_until_chr(char *str, char chr);

#endif