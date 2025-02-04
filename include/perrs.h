/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perrs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:03:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/04 11:53:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PERRS_H
# define PERRS_H

// All functions:
// - Print to stder (fd 2)
// - Return the number 1 (to support one-lining in conditional syntax)

// Print "Error\n" 
int	perr_titled(char *text);

// Print the provided text
int	perr(char *text);

// Call `perror` (print the provided text, a colon, and the errno text)
int	perrno(char *precolon, int errnum);

#endif