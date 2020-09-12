/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:41:23 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 01:44:09 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MSH_TOK_DELIM	" \t\r\n\a"

int			msh_execute(char *[]argv)
{
	size_t	i;

	if (argv[0] == NULL)
		return (1);
	i = 0;
	while (i < msh_num_builtins())
	{
		if (ft_strcmp(argv[0], builtin_str[i]))
			return ((*builin_func[i])(argv));
		i++;
	}
	return (msh_launch(argv));
}
