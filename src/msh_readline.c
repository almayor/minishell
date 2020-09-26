/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/26 20:11:40 by unite             #+#    #+#             */
/*   Updated: 2020/09/26 20:12:03 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_readline(const char *prompt)
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
