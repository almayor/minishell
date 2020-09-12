/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 01:04:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 02:10:35 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	copy_environ(void)
{
	char	**env;
	size_t	i;

	env = ft_xmalloc(sizeof(environ));
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		i++;
	}
	env[i] = NULL;
	environ = env;
}

int	main(int argc, char const *argv[])
{
	copy_environ();
	msh_loop();
}
