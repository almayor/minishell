/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 19:33:19 by unite             #+#    #+#             */
/*   Updated: 2020/07/16 02:41:56 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replicates behaviour of `strncmp` from `libc`.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *s1u;
	unsigned char *s2u;

	s1u = (unsigned char *)s1;
	s2u = (unsigned char *)s2;
	while ((*s1u || *s2u) && n-- > 0)
	{
		if (*s1u - *s2u)
			return (*s1u - *s2u);
		s1u++;
		s2u++;
	}
	return (0);
}
