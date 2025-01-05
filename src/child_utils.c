/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:08:21 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/05 18:02:49 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child(int input_fd, int output_fd, char *cmd, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error_exit("ERROR FORK");
	if (pid == 0)
	{
		redirect(input_fd, output_fd);
		run_command(cmd, env);
	}
}

void	redirect(int input_fd, int output_fd)
{
	int	dup_in;
	int	dup_out;

	dup_in = dup2(input_fd, STDIN_FILENO);
	dup_out = dup2(output_fd, STDOUT_FILENO);
	if (dup_in == -1 || dup_out == -1)
		error_exit("ERROR: ECHEC IN THE REDIRECTION\n");
	close(input_fd);
	close(output_fd);
}

void	wait_for_all_children()
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			ft_putendl_fd("WARNING PROCESS FAILED\n", 2);
	}
}

void	run_command(char *cmd, char **env)
{
	char	**args;
	char	*resolved_cmd;

	args = ft_split(cmd, ' ');
	if (!args)
		error_exit("ERROR FAILED TO PARSE COMMAND ARGUMENT\n");
	resolved_cmd = find_command_path(args[0], env);
	if (!resolved_cmd)
		error_exit("ERROR COMMAND NOT FOUND\n");
	execve(resolved_cmd, args, env);
	ft_putstr_fd("ERROR FAILED TO EXECUTE COMMAND\n", 2);
	ft_putendl_fd(cmd, 2);
	free(resolved_cmd);
	free_split(args);
	exit(1);
}
