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

static char	*append_string(char *str, char *buff, int str_size, int newline_idx)
{
	int			buff_size;
	char		*result;

	if (buff[0] == '\0')
		return (str);
	if (newline_idx != -1)
		buff_size = newline_idx;
	else
		buff_size = ft_strlen(buff);
	result = malloc((str_size + buff_size + 1) * sizeof(char));
	if (!result)
		return (free(str), NULL);
	ft_memmove(result, str, str_size);
	ft_memmove(result + str_size, buff, buff_size);
	result[str_size + buff_size] = '\0';
	ft_memmove(buff, buff + buff_size + (newline_idx != -1),
		BUFFER_SIZE - buff_size + 1 + (newline_idx != -1));
	return (free(str), result);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	t_gnl		gnl;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	gnl = (t_gnl){0};
	gnl.bytes = ft_strlen(buffer);
	while (true)
	{
		gnl.newline_idx = ft_idxof(buffer, '\n');
		gnl.res = append_string(gnl.res, buffer, gnl.ressize, gnl.newline_idx);
		if (gnl.newline_idx == -1)
			gnl.ressize += gnl.bytes;
		else
			gnl.ressize += gnl.newline_idx + 1;
		if (gnl.newline_idx != -1)
			return (gnl.res);
		gnl.bytes = read(fd, buffer, BUFFER_SIZE);
		if (gnl.bytes < 0)
			return (free(gnl.res), NULL);
		buffer[gnl.bytes] = '\0';
		if (gnl.bytes == 0)
			return (gnl.res);
	}
	return (gnl.res);
}

// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc != 2)
// 		return (write(2, "Usage: ", 7), write(2, argv[0], ft_strlen(argv[0])),
// 			write(2, " <file>\n", 8), 1);
// 	fd = open(argv[1], O_RDONLY);
// 	if (fd < 0)
// 		return (write(2, "Error: cannot open file\n", 25), 1);
// 	line = get_next_line(fd);
// 	write(1, "[", 1);
// 	write(1, line, ft_strlen(line));
// 	write(1, "]", 2);
// 	while (line)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		write(1, "[", 1);
// 		write(1, line, ft_strlen(line));
// 		write(1, "]", 2);
// 		write(1, "\n", 1);
// 	}
// 	return (close(fd), 0);
// }