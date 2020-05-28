/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: Wester <Wester@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/29 15:42:29 by Wester        #+#    #+#                 */
/*   Updated: 2020/05/26 13:32:33 by Wester        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char        *remove_start(char **args)
{
	int i;
	char *str;

	i = 0;
	if (!(args[0][0] == '.' && args[0][1] == '/'))
		return (args[0]);
	str = malloc(ft_strlen(args[0]) - 1);
	if (str == NULL)
		exit(errno);
	while (args[0][i + 2])
	{
		str[i] = args[0][i + 2];
		i++;
	}
	str[i] = 0;
	free(args[0]);
	return (str);
}

void		remove_quotes(char **args)
{
	int i;
	
	i = 0;
	while (args[i])
	{
		args[i] = ft_strstrip(args[i], '\"');
		i++;
	}
}

void        ft_execute(char **args, t_vars *p)
{
	int i;
	int test;

	i = 0;
	remove_quotes(args);
	args[0] = remove_start(args);
	if (fork() == 0)
	{
		test = execve(args[0], args, NULL);
		p->is_child = 0;
		exit(127);
	}
	wait(&i);
	if (WIFEXITED(i))
		p->ret = WEXITSTATUS(i);
	if (WIFSIGNALED(i))
	{
		p->ret = WTERMSIG(i);
		if (p->ret == 2)
		{
			p->ret = 130;
			p->is_child = 1;
		}
		if (p->ret == 3)
		{
			p->ret = 131;
			p->is_child = 2;
		}
	}
}