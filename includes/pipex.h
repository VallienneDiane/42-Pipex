/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:49:45 by dvallien          #+#    #+#             */
/*   Updated: 2022/01/20 17:45:05 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

typedef struct s_cmd
{
	int		fd_1;
	int		fd_2;
	char	**cmd_1;
	char	**cmd_2;
	char	*line_path;
	char	**path_tab;
	char	*path_1;
	char	*path_2;
}			t_cmd;

int		main(int ac, char **av, char **envp);
void	ft_open_files(char **av, t_cmd *cmd);
void	ft_get_cmd(char **av, t_cmd *cmd);
char	*ft_get_line_path(char **env);

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *src);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);

int		ft_pipex(t_cmd *cmd, char **envp);
char	*ft_access_path(char **av, char *cmd_name, t_cmd *cmd);
void	ft_error_access(char **av, char *path, t_cmd *cmd, char *cmd_name);
void	ft_process(pid_t pid1, pid_t pid2, t_cmd *cmd, char **envp);
void	ft_first_child(int *pipefd, pid_t pid1, t_cmd *cmd, char **envp);
void	ft_second_child(int *pipefd, pid_t pid2, t_cmd *cmd, char **envp);

void	ft_free_cmd(t_cmd *cmd);
void	ft_free(char **tab);

#endif