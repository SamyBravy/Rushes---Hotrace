/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/24 16:01:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_entry	*new_entry(size_t key, char *value)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	if (!entry)
		return (NULL);
	entry->key = key;
	entry->value = value;
	entry->value_len = ft_strlen(value);
	return (entry);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	d = dest;
	s = (unsigned char *)src;
	if (d == s)
		return (dest);
	if (d >= s && d <= s + n)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
		return (dest);
	}
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
	if (!ptr)
		return (NULL);
	i = -1;
	while (++i < total_size)
		ptr[i] = 0;
	return (ptr);
}
