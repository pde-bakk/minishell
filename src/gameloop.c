/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gameloop.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Peer <pde-bakk@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/04 14:39:32 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/06 20:21:07 by Peer          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**trimargs(char **args)
{
	int		i;
	int		len;
	char	**out;

	i = 0;
	len = 0;
	while (args[len] && ft_strncmp(args[len], "", 1) != 0 &&
	ft_strncmp(args[len], "<", 2) != 0 && ft_strncmp(args[len], ">", 2) != 0
	&& ft_strncmp(args[len], ">>", 3) != 0)
		len++;
	out = malloc((1 + len) * sizeof(char*));
	while (args[i] && i < len)
	{
		out[i] = ft_strdup(args[i]);
		i++;
	}
	out[i] = NULL;
	return (out);
}

int		do_pipes_and_redirs(char **pipesplitcmds, int n, t_vars *p)
{
	t_dup	redirs;
	char	**args;
	char	**trimmed;

	args = split_quotes2(pipesplitcmds[n]);
	ft_bzero(&redirs, sizeof(t_dup));
	redirect(args, &redirs);
	trimmed = trimargs(args);
	if (pipesplitcmds[n + 1])
		minipipe(pipesplitcmds, n, p);
	else if (args[0])
		argcheck(trimmed, p);
	reset_redirections(&redirs);
	free_args(trimmed);
	free_args(args);
	return (0);
}

int		gameloop(t_vars *p, char *line)
{
	int		i;
	int		n;
	char	**pipesplitcmds;
	char	**cmds;

	i = 0;
	cmds = NULL;
	if (line)
		cmds = ft_split_q(line, ';');
	while (cmds[i])
	{
		n = 0;
		pipesplitcmds = ft_split_q(cmds[i], '|');
		do_pipes_and_redirs(pipesplitcmds, n, p);
		i++;
		free_args(pipesplitcmds);
	}
	free_line_cmds(cmds, line, i);
	return (0);
}
