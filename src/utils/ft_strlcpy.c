/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 02:48:10 by unite             #+#    #+#             */
/*   Updated: 2020/07/16 02:44:20 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replicates behaviour of `strlcpy` from `libc`.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t maxlen)
{
	size_t srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < maxlen)
	{
		ft_memcpy(dst, src, srclen + 1);
	}
	else if (maxlen != 0)
	{
		ft_memcpy(dst, src, maxlen - 1);
		dst[maxlen - 1] = '\0';
	}
	return (srclen);
}
