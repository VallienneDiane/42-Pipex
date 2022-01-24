/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:53:12 by dvallien          #+#    #+#             */
/*   Updated: 2022/01/24 16:51:58 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_access_path(char **av, char *cmd_name, t_cmd *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = -1;
	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	while (cmd->path_tab[++i])
	{
		tmp = ft_strjoin(cmd->path_tab[i], "/");
		path = ft_strjoin(tmp, &cmd_name[0]);
		free(tmp);
		if (access(path, 0) == 0)
			return (path);
		else
		{
			free(path);
			path = NULL;
		}
	}
	ft_error_access(av, path, cmd, cmd_name);
	return (NULL);
}

void	ft_error_access(char **av, char *path, t_cmd *cmd, char *cmd_name)
{
	if (access(path, 0) == -1 && cmd_name == cmd->cmd_1[0])
	{
		ft_putstr_fd("zsh : command not found : ", 1);
		ft_putstr_fd(av[2], 1);
		ft_putstr_fd("\n", 1);
		return ;
	}
	else if (access(path, 0) == -1 && cmd_name == cmd->cmd_2[0])
	{
		ft_putstr_fd("zsh : command not found : ", 1);
		ft_putstr_fd(av[3], 1);
		exit(127);
	}
}
