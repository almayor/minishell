/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_statement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:24:12 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 22:32:35 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	count_tokens(const char *s)
{
	size_t count;
	size_t i;

	count = 1;
	i = 0;
	while (s[i])
	{
		if (ft_strchr(MSH_TOK_DELIM, s[i]))
			count++;
		i++;
	}
	return (count);
}

static char		**msh_tokenize(char *line)
{
	char	**tokens;
	char	*token;
	char	*ptr;
	size_t	position;

	tokens = ft_xcalloc(sizeof(char *), count_tokens(line) + 1);
	token = ft_strtok_r(line, MSH_TOK_DELIM, &ptr);
	position = 0;
	while (token != NULL)
	{
		if (ft_strlen(token) > 0)
			tokens[position++] = msh_expand(token);
		token = ft_strtok_r(NULL, MSH_TOK_DELIM, &ptr);
	}
	tokens[position++] = NULL;
	return (tokens);
}

int				msh_statement(const char *statement)
{
	char	*statement1;
	char	*cmd;
	char	**argv;
	char	*ptr;
	int		status;

	if (!(statement1 = ft_strdup(statement)))
		ft_terminate(MSH_ERR_MALLOC, 2);
	cmd = ft_strtok_r(statement1, ";", &ptr);
	status = 1;
	while (cmd && status)
	{
		argv = msh_tokenize(cmd);
		status = msh_execute(argv);
		ft_tabdel(argv);
		cmd = ft_strtok_r(NULL, ";", &ptr);
	}
	free(statement1);
	return (status);
}
