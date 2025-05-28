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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	result;

	__asm__ volatile (
		// Save registers we'll modify
		"push %%rcx\n"
		// Main comparison loop
		"1:\n"
		"movzbl (%0), %%eax\n" // Load byte from s1 into eax
		"movzbl (%1), %%ecx\n" // Load byte from s2 into ecx
		"incq %0\n"// Increment s1 pointer
		"incq %1\n"// Increment s2 pointer
		"testb %%al, %%al\n"// Check if we reached end of s1
		"je 2f\n"// If zero, exit loop
		"cmpb %%cl, %%al\n"// Compare bytes
		"je 1b\n"// If equal, continue loop
		// Exit point - compute difference
		"2:\n"
		"subl %%ecx, %%eax\n"// Compute difference
		"pop %%rcx\n"// Restore rcx
		: "=&S"(s1), "=&D"(s2), "=&a"(result)
		: "0"(s1), "1"(s2)
		: "memory", "cc");
	return (result);
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
