/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:31:15 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 04:37:07 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

const void	environ_shrink(void)
{
	size_t	len;
	size_t	i;
	char	**env;

	len = sizeof(environ) / sizeof(char *);
	env = ft_xcalloc(sizeof(char *), len - 1);
	i = 0;
	while (i < len)
	{
		if (environ[i])
			env[i] = environ[i];
		i++;
	}
	free(environ);
	environ = env;
}

int	unsetenv(const char *name)
{
	size_t	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)))
		{
			free(environ[i]);
			environ[i] = NULL;
			environ_shrink();
			return (0);
		}
		i++;
	}
	return (-1);
}
