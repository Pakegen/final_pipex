/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:07:57 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/05 18:05:04 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char *infile, char *cmd1, char *cmd2, char *outfile, char **env)
{
	int		pipefd[2];
	int		in_fd;
	int		out_fd;

	if (pipe(pipefd) == -1)
		error_exit("ERROR IN THE CREATION OF THE PIPE\n");
	in_fd = open_file(infile, O_RDONLY, 0);
	if (in_fd == -1)
		error_exit("ERROR INPUT CANNOT OPEN\n");
	out_fd = open_file(outfile, O_CREAT | O_WRONLY |O_TRUNC , 0644);
	if (out_fd == -1)
		error_exit("ERROR OUTPUT CANNOT OPEN\n");
	execute_pipeline(cmd1, cmd2, in_fd, out_fd, pipefd, env);
	close(in_fd);
	close(out_fd);
}

void	execute_pipeline(char *cmd1, char *cmd2, int in_fd, int out_fd, int *pipefd, char **env)
{
	create_child(in_fd, pipefd[1], cmd1, env);
	close(pipefd[1]);
	create_child(pipefd[0], out_fd, cmd2, env);
	close(pipefd[0]);
	wait_for_all_children();

}
