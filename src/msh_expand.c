/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:46:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/14 03:49:26 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*expand_tilde(const char *s)
{
	static char	buf[MSH_TOK_BUFSIZE];

	if (ft_strcmp(s, "~") == 0)
		ft_strlcpy(buf, ft_getenv("HOME"), MSH_TOK_BUFSIZE);
	else if (ft_strncmp(s, "~/", 2) == 0)
	{
		ft_strlcpy(buf, ft_getenv("HOME"), MSH_TOK_BUFSIZE);
		ft_strlcat(buf, s + 1, MSH_TOK_BUFSIZE);
	}
	else
		return (s);
	return (buf);
}

static char	*extract_variable(const char *s)
{
	size_t	i;
	char	*var;

	i = 0;
	while (s[i] && s[i] != '_' && ft_isalnum(s[i]))
		i++;
	if (!(var = ft_strndup(s, i)))
		ft_terminate(MSH_ERR_MALLOC, 2);
	return (var);
}

static const char	*expand_parameters(const char *s)
{
	static char	buf[MSH_TOK_BUFSIZE];
	const char	*start;
	const char	*end;
	char		*var;

	buf[0] = 0;
	start = s;
	while ((end = ft_strchr(start, '$')))
	{
		if (*start != '$')
			ft_strncat(buf, start, end - start);
		var = extract_variable(end + 1);
		ft_strlcat(buf, ft_getenv(var) ? ft_getenv(var) : "", MSH_TOK_BUFSIZE);
		start = end + 1 + ft_strlen(var);
		free(var);
	}
	ft_strlcat(buf, start, MSH_TOK_BUFSIZE);
	return (buf);
}

static const char	*remove_quotes(const char *s)
{
	static char	buf[MSH_TOK_BUFSIZE];
	size_t		len;
	size_t		i;

	len = ft_strlen(s);
	if (s[0] == '"' && s[len - 1] == '"')
		return (ft_strncpy(buf, s + 1, len - 2));
	if (s[0] == '\'' && s[len - 1] == '\'')
		return (ft_strncpy(buf, s + 1, len - 2));
	else
		return (s);
}

char		*msh_expand(const char *s)
{
	char	*s1;

	s = remove_quotes(s);
	s = expand_tilde(s);
	s = expand_parameters(s);
	if (!(s1 = ft_strdup(s)))
		ft_terminate(MSH_ERR_MALLOC, 2);
	return (s1);
}
