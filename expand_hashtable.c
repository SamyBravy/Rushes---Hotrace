/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuele <samuele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:25:25 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/25 16:39:48 by samuele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void	reassign_entries(t_data *data,
	t_entry **new_hashtable, size_t new_size)
{
	size_t	j;
	int		i;
	size_t	k;

	i = 0;
	while (i < data->hashtable_size)
	{
		if (data->hashtable[i])
		{
			k = 0;
			j = get_hash(new_size, data->hashtable[i]->key, 0);
			while (new_hashtable[j] != NULL)
			{
				j = get_hash(new_size, data->hashtable[i]->key, k);
				k++;
			}
			new_hashtable[j] = data->hashtable[i];
		}
		i++;
	}
	free(data->hashtable);
	data->hashtable = new_hashtable;
	data->hashtable_size = new_size;
}

static inline bool	is_prime(int n)
{
	int	i;

	if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0)
		return (false);
	i = 11;
	while (i * i <= n)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return (false);
		i += 6;
	}
	return (true);
}

int	next_prime(int n)
{
	int	r;

	if (n % 2 == 0)
		n++;
	r = n % 6;
	if (r == 0)
		n += 1;
	else if (r == 2)
		n += 3;
	else if (r == 3)
		n += 2;
	else if (r == 4)
		n += 1;
	while (1)
	{
		if (is_prime(n))
			return (n);
		if (n % 6 == 5)
			n += 2;
		else
			n += 4;
	}
}

void	expand_hashtable(t_data *data)
{
	int		new_size;
	t_entry	**new_hashtable;

	new_size = next_prime(data->hashtable_size * 2);
	new_hashtable = ft_calloc(new_size, sizeof(t_entry *));
	reassign_entries(data, new_hashtable, new_size);
}
