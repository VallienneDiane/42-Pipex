/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:56:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/01/19 18:03:06 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_first_child(int *pipefd, pid_t pid1, t_cmd *cmd, char **envp)
{
	int	fd;

	fd = 0;
	if (pid1 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (dup2(cmd->fd_1, STDIN_FILENO) < 0)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, 0);
	}
	dup2(cmd->fd_1, STDIN_FILENO);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(cmd->fd_1);
	if (cmd->path_1)
		execve(cmd->path_1, cmd->cmd_1, envp);
	else
		exit(1);
}

void	ft_second_child(int *pipefd, pid_t pid2, t_cmd *cmd, char **envp)
{
	if (pid2 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	dup2(pipefd[0], STDIN_FILENO);
	dup2(cmd->fd_2, STDOUT_FILENO);
	close(pipefd[1]);
	close(cmd->fd_2);
	if (cmd->path_2)
		execve(cmd->path_2, cmd->cmd_2, envp);
	else
		exit(1);
}

void	ft_process(pid_t pid1, pid_t pid2, t_cmd *cmd, char **envp)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (cmd->fd_1 >= 0)
	{
		pid1 = fork();
		if (pid1 == 0)
			ft_first_child(pipefd, pid1, cmd, envp);
	}
	pid2 = fork();
	if (pid2 == 0 && cmd->fd_2 >= 0)
		ft_second_child(pipefd, pid2, cmd, envp);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	ft_pipex(t_cmd *cmd, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid2 = 0;
	pid1 = 0;
	ft_process(pid1, pid2, cmd, envp);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	return (WEXITSTATUS(status));
}
