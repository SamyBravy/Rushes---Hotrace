/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/25 15:16:51 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

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

t_entry	*new_entry(t_key key, char *value)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	entry->key = key.key;
	entry->key_len = key.len;
	entry->value = value;
	entry->value_len = ft_strlen(value);
	return (entry);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dest;
	s = (unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_calloc(size_t n, size_t size)
{
	const size_t	total_size = n * size;
	size_t			i;
	char			*ptr;

	ptr = malloc(total_size);
	i = -1;
	while (++i < total_size)
		ptr[i] = 0;
	return (ptr);
}
