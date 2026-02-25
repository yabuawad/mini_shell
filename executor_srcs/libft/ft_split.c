/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malhassa <malhassa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:40:39 by malhassa          #+#    #+#             */
/*   Updated: 2025/08/25 17:45:24 by malhassa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countwords(char const *s, char c)
{
	int	counter;
	int	ccheck;
	int	i;

	i = 0;
	counter = 0;
	ccheck = 0;
	while (s[i])
	{
		if (s[i] != c && !ccheck)
		{
			ccheck = 1;
			counter++;
		}
		else if (s[i] == c)
			ccheck = 0;
		i++;
	}
	return (counter);
}

static int	lentillfound(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*wordspliter(char const *s, char c)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = (char *)malloc(lentillfound(s, c) + 1);
	if (!ptr)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	**freeptr(char **ptr, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**largeptr;
	int		j;

	largeptr = malloc((countwords(s, c) + 1) * sizeof(char *));
	if (!largeptr)
		return (NULL);
	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s != c && *s)
		{
			largeptr[j] = wordspliter(s, c);
			if (!largeptr[j])
				return (freeptr(largeptr, j));
			j++;
		}
		while (*s && *s != c)
			s++;
	}
	largeptr[j] = NULL;
	return (largeptr);
}

// void print_split(char **arr) {
//     int i = 0;

//     if (arr == NULL) {
//         printf("NULL\n");
//         return ;
//     }

//     while (arr[i] != NULL) {
//         printf("[%s]\n", arr[i]);
//         i++;
//     }
//     printf("----\n");
// }

// int main(void) {
//     char **result;

//     result = ft_split("hello!",' ');
// 	print_split(result);

//     return (0);
// }