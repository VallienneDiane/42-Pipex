/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:02:08 by dvallien          #+#    #+#             */
/*   Updated: 2022/01/20 17:43:56 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_open_files(char **av, t_cmd *cmd)
{
	cmd->fd_1 = open(av[1], O_RDONLY);
	cmd->fd_2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (cmd->fd_1 < 0)
	{
		strerror(cmd->fd_1);
		return ;
	}
	if (cmd->fd_2 < 0)
		strerror(cmd->fd_2);
}

void	ft_get_cmd(char **av, t_cmd *cmd)
{
	cmd->cmd_1 = ft_split(av[2], ' ');
	cmd->cmd_2 = ft_split(av[3], ' ');
}

char	*ft_get_line_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	ft_free_cmd(t_cmd *cmd)
{
	ft_free(cmd->cmd_1);
	ft_free(cmd->cmd_2);
	ft_free(cmd->path_tab);
	free(cmd->path_1);
	free(cmd->path_2);
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	cmd;
	int		status;

	if (ac == 5)
	{
		ft_open_files(av, &cmd);
		ft_get_cmd(av, &cmd);
		cmd.line_path = ft_get_line_path(envp);
		cmd.path_tab = ft_split(cmd.line_path, ':');
		cmd.path_1 = ft_access_path(av, *cmd.cmd_1, &cmd);
		cmd.path_2 = ft_access_path(av, *cmd.cmd_2, &cmd);
		status = ft_pipex(&cmd, envp);
		ft_free_cmd(&cmd);
	}
	else
	{
		ft_putstr_fd("zsh : invalid number of arguments", 1);
		exit(EXIT_FAILURE);
	}
	return (0);
}
