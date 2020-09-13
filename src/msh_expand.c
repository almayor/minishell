/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:46:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 21:14:23 by unite            ###   ########.fr       */
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

static char	*string_replace(const char *s, const char *needle, const char *repl)
{
	size_t	count;
	size_t	len_needle;
	size_t	len_repl;
	char	*s1;
	char	*s2;

	count = string_count(s, needle);
	len_needle = ft_strlen(needle);
	len_repl = ft_strlen(repl);
	s1 = ft_xmalloc(ft_strlen(s) + (len_repl - len_needle) * count(s, needle));
	while ()
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