/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:44:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/05 17:44:00 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"

// static int	free_set(char **set)
// {
// 	size_t	i;

// 	i = 0;
// 	while (set[i])
// 		free(set[i++]);
// 	free(set);
// 	return (0);
// }

// static char	**malloc_by_sep(char const *s, char c)
// {
// 	char	**set;
// 	size_t	i;
// 	char	*next_sep;
// 	size_t	substr_len;
// 	size_t	substr_count;

// 	i = 0;
// 	substr_count = 0;
// 	while (s[i])
// 	{
// 		next_sep = ft_strchr(&s[i], c);
// 		if (next_sep)
// 			substr_len = next_sep - &s[i];
// 		else
// 			substr_len = ft_strlen(&s[i]);
// 		if (!substr_len)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		substr_count++;
// 		i += substr_len;
// 	}
// 	set = ft_calloc(substr_count + 1, sizeof(char *));
// 	return (set);
// }

// static size_t	substr_remainder_by_sep(char const *s, char c, size_t s_i)
// {
// 	char	*pointer_to_next_sep;

// 	pointer_to_next_sep = ft_strchr(&s[s_i], c);
// 	if (pointer_to_next_sep)
// 		return (pointer_to_next_sep - &s[s_i]);
// 	else
// 		return (ft_strlen(&s[s_i]));
// }

// static int	fill_by_sep(char const *s, char c, char **set)
// {
// 	size_t	set_i;
// 	size_t	s_i;
// 	size_t	substr_len;
// 	char	*substr;

// 	set_i = 0;
// 	s_i = 0;
// 	while (s[s_i])
// 	{
// 		substr_len = substr_remainder_by_sep(s, c, s_i);
// 		if (substr_len == 0)
// 		{
// 			s_i++;
// 			continue ;
// 		}
// 		substr = ft_calloc(substr_len + 1, sizeof(char));
// 		if (substr == NULL)
// 			return (free_set(set));
// 		ft_strlcpy(substr, &s[s_i], substr_len + 1);
// 		s_i += substr_len;
// 		set[set_i++] = substr;
// 	}
// 	return (1);
// }

// static void	for_each_arg(char *cmd_str, bool(*f)(char *arg_start, int arg_len))
// {
// 	int		cmd_i;
// 	int		arg_i;
// 	bool	singlequoted;
// 	bool	doublequoted;
	
// 	cmd_i = 0;
// 	arg_i = 0;
// 	singlequoted = 0;
// 	doublequoted = 0;
// 	while (cmd_str)
// 	{
// 		if (!cmd_str[cmd_i] && cmd_i)
// 		{
			
// 		}
// 	}
// }


// char	**split_cmd(char *cmd_str, char c)
// {
// 	char	**set;

// 	if (!cmd_str)
// 		return (NULL);
// 	count()
// 	set = malloc_by_sep(s, c);
// 	if (!set)
// 		return (NULL);
// 	if (!fill_by_sep(s, c, set))
// 		return (NULL);
// 	return (set);
// }
