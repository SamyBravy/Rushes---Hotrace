/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/24 16:01:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	convert_to_int(char *key)
{
	int		i;
	size_t	res;
	size_t	pow;

	i = ft_strlen(key) - 1;
	res = 0;
	pow = 1;
	while (i >= 0)
	{
		res += (key[i] * pow);
		pow *= 128;
		i--;
	}
	return (res);
}

size_t	h1(t_data *data, size_t key)
{
	return (key % data->hashtable_size);
}

size_t	h2(t_data *data, size_t key)
{
	return (1 + (key % (data->hashtable_size - 1)));
}

size_t	get_hash(t_data *data, size_t key, int i)
{
	return ((h1(data, key) + h2(data, key) * i) % data->hashtable_size);
}
