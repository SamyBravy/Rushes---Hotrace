/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuele <samuele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/25 14:47:52 by samuele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	convert_to_int(char *key)
{
	int		i;
	size_t	res;
	size_t	pow;

	i = 0;
	res = 0;
	pow = 1;
	while (key[i])
	{
		res += (key[i] * pow);
		pow *= 128;
		i++;
	}
	return (res);
}

size_t	h1(size_t hashtable_size, size_t key)
{
	return (key % hashtable_size);
}

size_t	h2(size_t hashtable_size, size_t key)
{
	return (1 + (key % (hashtable_size - 1)));
}

size_t	get_hash(size_t hashtable_size, size_t key, int i)
{
	return ((h1(hashtable_size, key) + h2(hashtable_size, key) * i)
		% hashtable_size);
}
