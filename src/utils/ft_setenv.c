/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 04:16:04 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 04:36:41 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static char	*get_string(const char *name, const char *value)
{
	char	*s;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	s = ft_xmalloc(sizeof(char) * len);
	ft_strlcat(s, name, len);
	ft_strlcat(s, "=", len);
	ft_strlcat(s, value, len);
	return (s);
}

static void	environ_append(const char *s)
{
	char	**env;
	size_t	i;

	env = ft_xcalloc(sizeof(char *), sizeof(environ) / sizeof(char *) + 1);
	i = 0;
	while (environ[i])
	{
		env[i] = environ[i];
		i++;
	}
	env[i] = s;
	free(environ);
	environ = env;
}

int	ft_setenv(const char *name, const char *value, int overwrite)
{
	size_t	i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)))
		{
			if (overwrite)
			{
				free(environ[i]);
				environ[i] = get_string(name, value);
			}
			return (0);
		}
		i++;
	}
	environ_append(get_string(name, value));
	return (0);
}
