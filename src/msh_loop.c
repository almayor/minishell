/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 19:23:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/13 03:05:22 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t count_tokens(const char *s)
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

static char	**tokenize(char *line)
{
	char	**tokens;
	char	*token;
	char 	*ptr;
	size_t	position;

	tokens = ft_xcalloc(sizeof(char *), count_tokens(line) + 1);
	token = ft_strtok_r(line, MSH_TOK_DELIM, &ptr);
	position = 0;
	while (token != NULL)
	{
		if (ft_strlen(token) > 0)
			tokens[position++] = token;
		token = ft_strtok_r(NULL, MSH_TOK_DELIM, &ptr);
	}
	return (tokens);
}

void		msh_loop(void)
{
	char	*line;
	char 	*ptr;
	char 	*cmd;
	char	**argv;
	int		status;

	status = 1;
	rl_bind_key('\t', rl_complete);
	while (status && (line = readline(MSH_PROMPT)))
	{
		add_history (line);
		cmd = ft_strtok_r(line, ";", &ptr);
		while (cmd)
		{
			argv = tokenize(cmd);
			status = msh_execute(argv);
			free(argv);
			cmd = ft_strtok_r(NULL, ";", &ptr);
		}
		free(line);
	}
}
