/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/23 17:50:54 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft_full/libft_full.h"

// for VSCode
# ifndef O_DIRECTORY
#  define O_DIRECTORY __O_DIRECTORY
# endif

typedef struct s_shell
{
	int		argc;
	char	**argv;
	char	**envp;
	char	*bin_paths;
	int		waits;
	int		prev_read;
	int		pipe_read;
	int		pipe_write;
}			t_shell;

void	init_shell(t_shell *shell, int argc, char **argv, char **envp);
void	repipe(t_shell *shell);
void	unpipe(t_shell *shell);

void	process_cmd(t_shell *shell, char *cmd);
bool	cmd_is_empty_or_dir(char *cmd_str);

int		pipex_arg_errno(char *arg);

bool	free_str_arr(char **arr);
bool	close_all(t_shell *shell);
int		clean_exit(t_shell shell, int exit_code);

#endif