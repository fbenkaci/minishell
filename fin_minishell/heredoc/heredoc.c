/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbenkaci <fbenkaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:16 by fbenkaci          #+#    #+#             */
/*   Updated: 2026/06/18 17:04:53 by fbenkaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"
#include <signal.h>

void	check_heredoc_interrupts(int line_nb, char *delimiter, int *fd)
{
	ft_putstr_fd("\nminishell: warning: here-document at line ", 2);
	ft_putnbr_fd(line_nb, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted ", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
	(void)fd;
}

int	process_heredoc_line(t_struct **data, char *delimiter, int *fd,
		int *line_nb)
{
	char	buffer[1024];
	char	*line;
	char	*expanded_line;
	int		ret;

	write(1, "> ", 2);
	ret = read_heredoc_line(delimiter, *line_nb, buffer);
	if (ret == -1 || ret == -2)
		return (ret);
	if (ret == 0)
	{
		line = buffer;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
			&& line[ft_strlen(delimiter)] == '\n')
			return (-2);
		expanded_line = expand_variables_heredoc(data, line);
		if (expanded_line)
		{
			write(fd[1], expanded_line, ft_strlen(expanded_line));
			free(expanded_line);
		}
		(*line_nb)++;
	}
	return (1);
}

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_signal_status = 130;
	write(STDOUT_FILENO, "\n", 1);
}

int	heredoc_loop(t_struct **data, char *delimiter, int *fd)
{
	int	line_nb;
	int	ret;

	line_nb = 1;
	while (1)
	{
		ret = process_heredoc_line(data, delimiter, fd, &line_nb);
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			break ;
	}
	return (0);
}

int	heredoc_input(t_struct **data, char *delimiter)
{
	int					fd[2];
	int					ret;
	struct sigaction	old_sigint;
	struct sigaction	new_sigint;

	ret = 0;
	if (init_heredoc_pipe(fd) == -1)
		return (-1);
	new_sigint.sa_handler = handle_sigint_heredoc;
	sigemptyset(&new_sigint.sa_mask);
	new_sigint.sa_flags = 0;
	sigaction(SIGINT, &new_sigint, &old_sigint);
	ret = heredoc_loop(data, delimiter, fd);
	if (ret == -1)
		return (-1);
	sigaction(SIGINT, &old_sigint, NULL);
	close(fd[1]);
	return (fd[0]);
}
