/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 19:23:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/14 02:09:27 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_tokens(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

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

static char		**tokenize(char *line)
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
	return (tokens);
}

static char		*msh_readline(const char *prompt)
{
	char	*line;
	int		rc;

	ft_putstr(prompt);
	rc = get_next_line(0, &line);
	if (rc < 0)
		ft_terminate("failed to read a line", 2);
	if (rc == 0)
		return (NULL);
	else
		return (line);
}

void			msh_loop(void)
{
	char	*line;
	char	*ptr;
	char	*cmd;
	char	**argv;
	int		status;

	status = 1;
	while (status && (line = readline(msh_prompt())))
	{
		add_history(line);
		cmd = ft_strtok_r(line, ";", &ptr);
		while (cmd)
		{
			argv = tokenize(cmd);
			status = msh_execute(argv);
			free_tokens(argv);
			cmd = ft_strtok_r(NULL, ";", &ptr);
		}
		free(line);
	}
}
