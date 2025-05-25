/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/24 16:01:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	ft_idxof(char *str, char c)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == c)
			return (i);
	return (-1);
}

static char	*append_string(char *str, char *buff, int newline_idx)
{
	const int	str_size = ft_strlen(str);
	int			buff_size;
	char		*result;

	if (ft_strlen(buff) == 0)
		return (str);
	if (newline_idx != -1)
		buff_size = newline_idx;
	else
		buff_size = ft_strlen(buff);
	result = ft_calloc(str_size + buff_size + 1, sizeof(char));
	if (!result)
		return (free(str), NULL);
	ft_memmove(result, str, str_size);
	ft_memmove(result + str_size, buff, buff_size);
	ft_memmove(buff, buff + buff_size + (newline_idx != -1),
		BUFFER_SIZE - buff_size + 1);
	return (free(str), result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*result;
	ssize_t		bytes;
	int			newline_idx;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	result = NULL;
	while (true)
	{
		newline_idx = ft_idxof(buffer, '\n');
		result = append_string(result, buffer, newline_idx);
		if (newline_idx != -1)
			return (result);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(result), NULL);
		buffer[bytes] = '\0';
		if (bytes == 0)
			return (result);
	}
	return (result);
}
