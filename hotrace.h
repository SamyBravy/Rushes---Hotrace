/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odudniak <odudniak@student.42firenze.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/24 16:01:44 by odudniak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# ifndef HASH_TABLE_SIZE
#  define HASH_TABLE_SIZE 111427
# endif

typedef struct s_entry
{
	size_t	key;
	char	*value;
	int		value_len;

}	t_entry;

typedef enum e_state
{
	INS_KEY,
	INS_VALUE,
	SEARCH
}	t_state;

typedef struct s_data
{
	t_entry	**hashtable;
	int		hashtable_size;

}	t_data;

size_t	convert_to_int(char *key);
size_t	get_hash(t_data *data, size_t key, int i);

char	*get_next_line(int fd);
// UTILS
t_entry	*new_entry(size_t key, char *value);
int		ft_strlen(char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t n, size_t size);

#endif
