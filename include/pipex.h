/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:29:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 21:34:41 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include "../libft_full/libft_full.h"
# include "perrs.h"

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

bool	init_shell(t_shell *shell, int argc, char **argv, char **envp);
void	repipe(t_shell *shell);

void	process_cmd(t_shell *shell, char *cmd);
char	*path_to_binary(t_shell *shell, char *bin);

bool	free_str_arr(char **arr);
bool	if_either(int first, int second);
bool	close_until_negative(int *fds);
bool	cmd_is_empty_or_dir(char *cmd_str);

int		close_both_unless_pipe(t_shell *shell, int fd1, int fd2);
void	pipes_bnegative(t_shell *shell);
int		clean_exit(t_shell shell, int exit_code);

#endif