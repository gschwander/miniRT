/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_ft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:43:11 by gschwand          #+#    #+#             */
/*   Updated: 2025/05/22 11:43:14 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	ft_check_chr_chr(char c, char set)
{
	if (c == set)
		return (1);
	else
		return (0);
}

static int	ft_countword(const char *s, char c)
{
	int	index;
	int	word;
	int	letter;

	index = 0;
	letter = 0;
	word = 0;
	while (index == 0 || s[index - 1])
	{
		if ((ft_check_chr_chr(s[index], c) == 1 || !s[index]) && letter > 0)
		{
			word++;
			letter = 0;
		}
		else if (ft_check_chr_chr(s[index], c) == 0)
			letter++;
		index++;
	}
	return (word);
}

static int	ft_alloc_words(t_rt *rt, const char *s, char c, char **tab)
{
	int	index;
	int	word;
	int	letter;

	index = 0;
	letter = 0;
	word = 0;
	while (index == 0 || s[index - 1])
	{
		if ((ft_check_chr_chr(s[index], c) == 1 || !s[index]) && letter > 0)
		{
			tab[word] = wrap_malloc(rt, (letter + 1) * sizeof(char));
			ft_strlcpy(tab[word], s + index - letter, letter + 1);
			word++;
			letter = 0;
		}
		else if (ft_check_chr_chr(s[index], c) == 0)
			letter++;
		index++;
	}
	tab[word] = NULL;
	return (word);
}

char	**rt_ft_split(t_rt *rt, char const *s, char c)
{
	int		countword;
	char	**tab;

	if (!s)
		return (NULL);
	countword = ft_countword(s, c);
	tab = wrap_malloc(rt, (countword + 1) * sizeof(char *));
	ft_alloc_words(rt, s, c, tab);
	return (tab);
}
