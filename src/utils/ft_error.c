/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 00:23:14 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 20:34:56 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_error(const char *mes)
{
	char *file_name;

	if (ft_strrchr(__FILE__, '/'))
		file_name = ft_strrchr(__FILE__, '/');
	else
		file_name = __FILE__;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", file_name, mes);
}
