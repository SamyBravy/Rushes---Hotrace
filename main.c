/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/24 16:01:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"
#include <time.h>
#include <stdio.h>

void	insert(t_data *data, t_key key, char *value)
{
	int		i;
	size_t	j;

	i = 0;
	while (i < data->hashtable_size)
	{
		j = get_hash(data->hashtable_size, key.key, i);
		if (data->hashtable[j] == NULL)
		{
			data->hashtable[j] = new_entry(key, value);
			return ;
		}
		i++;
	}
	expand_hashtable(data);
	insert(data, key, value);
}

int	search(t_data *data, char *key_str, size_t key)
{
	int		i;
	size_t	j;

	i = 0;
	j = get_hash(data->hashtable_size, key, i);
	while (i < data->hashtable_size && data->hashtable[j] != NULL)
	{
		if (data->hashtable[j]->key == key
			&& data->hashtable[j]->key_len == ft_strlen(key_str))
		{
			write(1, data->hashtable[j]->value, data->hashtable[j]->value_len);
			return (write(1, "\n", 1));
		}
		i++;
		j = get_hash(data->hashtable_size, key, i);
	}
	write(1, key_str, ft_strlen(key_str));
	write(1, ": Not found.\n", 13);
	return (0);
}

void	free_all(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->hashtable_size)
	{
		if (data->hashtable[i])
		{
			free(data->hashtable[i]->value);
			free(data->hashtable[i]);
		}
		i++;
	}
	free(data->hashtable);
}

int	main(void)
{
	char	*line;
	t_state	state;
	t_key	key;
	t_data	data;

	clock_t	start_time;
	start_time = clock();
	data = (t_data){.hashtable = NULL, .hashtable_size = HASH_TABLE_SIZE / 2};
	state = INS_KEY;
	line = get_next_line(0);
	expand_hashtable(&data);
	while (line)
	{
		if (state == INS_KEY)
			key = (t_key){convert_to_int(line), ft_strlen(line)};
		else if (state == INS_VALUE)
			insert(&data, key, line);
		else if (state == SEARCH)
			search(&data, line, convert_to_int(line));
		if (state == INS_KEY && line[0] == '\0')
			state = SEARCH;
		if (state != INS_VALUE)
			free(line);
		if (state != SEARCH)
			state = (state + 1) % SEARCH;
		line = get_next_line(0);
	}
	free_all(&data);
	clock_t	end_time = clock();
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	printf("Elapsed time: %.2f seconds\n", elapsed_time);
	return (0);
}
