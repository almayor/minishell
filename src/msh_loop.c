/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 19:23:20 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 01:16:16 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*msh_read_line(void)
{
	char	*line;

	if (feof(stdin))
		line = NULL;
	else if (get_next_line(0, &line) < 0)
		ft_terminate("couldn't read line", 0, EXIT_FAILURE);
	return (line);
}

char	**msh_split_line(const char *line)
{
	size_t	position;
	size_t	ntokens;
	char	**tokens;
	char	*token;

	position = 0;
	ntokens = ft_strcount(line, MSH_TOK_DELIM);
	tokens = ft_xcalloc(sizeof(char *), ntokens + 1);
	token = ft_strtok(line, MSH_TOK_DELIM);
	while (token != NULL)
	{
		tokens[position++] = token;
		token = ft_strtok(NULL, MSH_TOK_DELIM);
	}
	return (tokens);
}

void	msh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		ft_putstr("$> ");
		line = msh_read_line(&line);
		args = msh_split_line(line);
		status = msh_execute(args[0], args + 1);

		free(line);
		free(args);
	}
}