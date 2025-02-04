/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/04 13:22:05 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
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
	char		**bin_paths;
}					t_shell;

int		pipex(int argc, char **args, char **envp);
int		here_doc(char **args);

void	run_cmd(int argc, char **argv, char **envp, int target_fd);
t_cmd	args_to_cmd(int argc, char **argv);

char *path_to_binary(char **envp, char *cmd);

bool	is_operator(char *arg);
void	*free_str_arr(char **arr, size_t len);
size_t	len_until_chr(char *str, char chr);

#endif