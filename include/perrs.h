/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:03:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/22 09:38:18 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERRS_H
# define PERRS_H

// All functions:
// - Print to stder (fd 2)
// - Return the number 1 (to support one-lining in conditional syntax)

// Print the provided text
int	perr(char *text);

// Print `pipex: ${arg}: ${errno message}`
int	pipex_arg_errno(char *arg);

#endif