/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samuele <samuele@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 16:01:21 by odudniak          #+#    #+#             */
/*   Updated: 2025/05/25 16:35:14 by samuele          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024 // ridurre per prendere un punteggio più alto al test hard
# endif

# ifndef HASH_TABLE_SIZE
#  define HASH_TABLE_SIZE 111427 // ridurre per prendere un punteggio più alto al test hard
# endif

typedef struct s_entry
{
	size_t		key;
	char		*key_str;
	char		*value;
	size_t		value_len;
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
	int		inserted;
}	t_data;

typedef struct s_key
{
	size_t	key;
	char	*str;
}	t_key;

size_t	convert_to_int(char *key);
size_t	get_hash(size_t hashtable_size, size_t key, int i);

void	expand_hashtable(t_data *data);

typedef struct s_gnl
{
	ssize_t		bytes;
	int			newline_idx;
	char		*res;
	int			ressize;
}	t_gnl;

char	*get_next_line(int fd);
// UTILS
void	free_all(t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(char *str);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_calloc(size_t n, size_t size);

#endif
