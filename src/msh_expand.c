/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:46:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 14:12:58 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count(const char *haystack, const char *needle)
{
	size_t	count;

	count = 0;
	while ((haystack = ft_strstr(haystack, needle)))
		count++;
	return (count);
}

static void string_replace(char **s, const char *needle, const char *repl)
{
	char	*s1;
	char	*p1;
	char	*p_start;
	char	*p_end;

	s1 = ft_xmalloc(
		sizeof(char),
		ft_strlen(*s) + 
		(ft_strlen(repl) - ft_strlen(needle)) * count(*s, needle));
	p1 = s1;
	p_start = *s;
	while ((p_end = ft_strstr(p_start, needle)))
	{
		ft_strncpy(p1, p_start, p_end - p_start);
		p1 += p_end - p_start;
		ft_strcpy(p1, repl);
		p1 += ft_strlen(repl);
		p_start = p_end + ft_strlen(needle);
	}
	ft_stcpy(p1, p_start);
	free(*s);
	*s = s1;
}

static char	*expand_tilde(char *s)
{
	char	*ptr;
	char	*s1;

	ptr = ft_strchr(s, '~');
	while (ptr)
	{

	}
}
char	*msh_expand(char *s)
{

}