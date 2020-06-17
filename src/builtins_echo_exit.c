/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_echo_exit.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: pde-bakk <pde-bakk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/17 16:22:12 by pde-bakk      #+#    #+#                 */
/*   Updated: 2020/06/17 16:22:43 by pde-bakk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(char **args, t_vars *p, int fd)
{
	int i;

	i = 1;
	if (args[1] && ft_strncmp(args[1], "-n", 3) == 0)
		i = 2;
	while (args[i])
	{
		write_instant(args[i], fd, p);
		i++;
		if (args[i] != 0)
			ft_putchar_fd(' ', fd);
	}
	if (!args[1] || (args[1] && ft_strncmp(args[1], "-n", 3) != 0))
		ft_putchar_fd('\n', fd);
	return (0);
}

void	our_exit(char **args, t_vars *p)
{
	int stat;
	int	i;

	(void)p;
	i = 0;
	if (args[1] == NULL)
		exit(0);
	if (args[1] && args[2])
	{
		ft_dprintf(2, "bash: exit: too many arguments\n");
		return ;
	}
	while (args[1][i])
	{
		if (ft_isdigit(args[i][i]) == 0)
		{
			ft_dprintf(2, "bash: exit: %s: numeric argument required\n",
			args[1]);
			return ;
		}
		i++;
	}
	stat = ft_atoi(args[1]);
	exit(stat);
}
