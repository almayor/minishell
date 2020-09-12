/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:33:19 by unite             #+#    #+#             */
/*   Updated: 2020/07/16 02:50:39 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replicates `strcmp` from `libc`.
*/

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s1u;
	unsigned char	*s2u;

	s1u = (unsigned char *)s1;
	s2u = (unsigned char *)s2;
	while (*s1u || *s2u)
	{
		if (*s1u - *s2u)
			return (*s1u - *s2u);
		s1u++;
		s2u++;
	}
	return (0);
}
