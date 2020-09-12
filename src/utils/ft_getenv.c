/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:35:41 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 20:16:35 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_getenv(const char *name)
{
	static char	*empty = "";
	size_t		i;
	size_t		len;

	len = ft_strlen(name);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], name, len) == 0)
			return (environ[i] + len + 2);
		i++;
	}
	return (empty);
}
