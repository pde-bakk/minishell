/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_quotes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/13 13:19:16 by Wester        #+#    #+#                 */
/*   Updated: 2020/04/17 14:18:06 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int 		find_quote(char *str, int *i)
{
	int ret;

	ret = *i;
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"' && str[*i] != 0)
			(*i)++;
		(*i)++;
	}
	return (*i - ret);
}

int         ft_words(char *str)
{
	int i;
	int words;

	words = 0;
	i = 0;
	while (str[i])
	{
		words++;
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		find_quote(str, &i);
		while (!(str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i] != 0)
			i++;
	}
	return (words);
}

char        **ft_free(char **arr, int count)
{
	while (count >= 0)
	{
		free(arr[count]);
		count--;
	}
	free(arr);
	return (NULL);
}

char		*make_quote(char *str, int *i)
{
	char 	*word;
	int 	k;

	k = *i;
	word = malloc(find_quote(str, &k) + 1);
	if (!word)
		return (NULL);
	k = 0;
	word[k] = str[*i];
	k++;
	(*i)++;
	while (str[*i] != '\"' && str[*i] != 0)
	{
		word[k] = str[*i];
		k++;
		(*i)++;
	}
	word[k] = '\"';
	word[k + 1] = 0;
	return (word);
}

char        *find_word(char *str, int *i)
{
	int k;
	char *word;

	k = *i;
	if (str[k] == '\"')
		return (make_quote(str, i));
	while (str[k] != 32 && !(str[k] >= 9 && str[k] <= 13) && str[k] != 0)
		k++;
	word = malloc(k - *i + 1);
	if (word == NULL)
		return (NULL);
	k = 0;
	while (str[*i] != 32 && !(str[*i] >= 9 && str[*i] <= 13) && str[*i] != 0)
	{
		word[k] = str[*i];
		(*i)++;
		k++;
	}
	word[k] = 0;
	return (word);
}

char        **split_quotes(char *str)
{
	char **arr;
	int count;
	int i;

	i = 0;
	count = 0;
	arr = malloc((sizeof (char *) * ft_words(str)) + 1);
	while (str[i])
	{
		while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] != 0)
		{
			arr[count] = find_word(str, &i);
			if (arr[count] == NULL)
				return (ft_free(arr, count));
			count++;
		}
	}
	arr[count] = 0;
	return (arr);
}