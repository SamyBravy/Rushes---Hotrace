/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_hashtable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 14:25:25 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/25 15:14:03 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void	reassign_entries(t_data *data,
	t_entry **new_hashtable, size_t new_size)
{
	size_t	j;
	int		i;

	i = 0;
	while (i < data->hashtable_size)
	{
		if (data->hashtable[i])
		{
			j = get_hash(new_size, data->hashtable[i]->key, 0);
			while (new_hashtable[j] != NULL)
				j = get_hash(new_size, data->hashtable[i]->key, j + 1);
			new_hashtable[j] = data->hashtable[i];
		}
		i++;
	}
	free(data->hashtable);
	data->hashtable = new_hashtable;
	data->hashtable_size = new_size;
}

void	expand_hashtable(t_data *data)
{
	int		new_size;
	t_entry	**new_hashtable;

	new_size = data->hashtable_size * 2 + 1;
	new_hashtable = ft_calloc(new_size, sizeof(t_entry *));
	if (!data->hashtable)
	{
		data->hashtable = new_hashtable;
		data->hashtable_size = new_size;
		return ;
	}
	reassign_entries(data, new_hashtable, new_size);
}
