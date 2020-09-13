/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:46:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 16:10:02 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*expand_parameters(const char *s)
{
	static char	buf[MSH_BUFSIZE];
	char		*var;
	const char	*start;
	const char	*end;

	buf[0] = 0;
	start = s;
	while ((end = ft_strchr(start, '$')))
	{
		if (*start != '$')
			ft_strncat(buf, start, end - start);
		var = extract_variable(end + 1);
		ft_strcat(buf, ft_getenv(var) ? ft_getenv(var) : "");
		start = end + 1 + ft_strlen(var);
		free(var);
	}
	ft_strcat(buf, start);
	return (ft_strdup(buf));
}

char	*msh_expand(const char *s)
{
	char	*s_expanded;

	if (ft_strcmp(s, "~") == 0)
		s_expanded = ft_strdup(ft_getenv("HOME") ? ft_getenv("HOME") : "");
	else if (ft_strcmp(s, "~-") == 0)
		s_expanded = ft_strdup(ft_getenv("OLDPWD") ? ft_getenv("OLDPWD") : "");
	else if (ft_strcmp(s, "~+") == 0)
		s_expanded = ft_strdup(ft_getenv("PWD") ? ft_getenv("PWD") : "");
	else
		s_expanded = expand_parameters(s);
	if (s_expanded == NULL)
		ft_terminate(MSH_ERR_MALLOC, 2);
	return (s_expanded);
}
