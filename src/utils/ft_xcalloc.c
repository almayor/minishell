/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unite <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 00:27:33 by unite             #+#    #+#             */
/*   Updated: 2020/09/12 21:18:40 by unite            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Replicates behaviour of `calloc` from `libc`, but fails on
** memory allocation errors.
*/

void	*ft_xcalloc(size_t count, size_t size)
{
	void	*mem;

	mem = ft_calloc(count, size);
	if (!mem && !size)
		ft_terminate("malloc error", 2);
	return (mem);
}
