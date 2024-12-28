/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinsecho <jinsecho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 18:08:12 by jinsecho          #+#    #+#             */
/*   Updated: 2024/03/27 21:57:34 by jinsecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *string)
{
	size_t	len;

	len = 0;
	while (*string)
	{
		string++;
		len++;
	}
	return (len);
}

char	*gnl_strchr(char *string, int c)
{
	char	*string1;
	int		i;

	if (string == NULL)
		return (NULL);
	i = 0;
	string1 = (char *)string;
	while (string1[i])
	{
		if (string1[i] == c)
			return (&string1[i]);
		i++;
	}
	if (c == 0)
		return (&string1[i]);
	return (NULL);
}

static void	join_input(char *ptr, char *s1, char *s2)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	i = 0;
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		ptr[s1_len + i] = s2[i];
		i++;
	}
	ptr[s1_len + i] = 0;
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr_arr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = gnl_strlen(s1);
	s2_len = gnl_strlen(s2);
	ptr_arr = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (ptr_arr == NULL)
	{
		free(s1);
		return (NULL);
	}
	join_input(ptr_arr, s1, s2);
	free(s1);
	return (ptr_arr);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*ptr_arr;
	size_t	i;
	size_t	k;

	if (s == NULL)
		return (NULL);
	k = gnl_strlen(s);
	if (k <= start || len == 0)
		return (gnl_strdup(""));
	ptr_arr = (char *)malloc(sizeof(char) * len + 1);
	if (ptr_arr == NULL)
	{
		free(s);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		ptr_arr[i] = s[start + i];
		i++;
	}
	ptr_arr[i] = 0;
	return (ptr_arr);
}
