/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 13:04:10 by qacjl             #+#    #+#             */
/*   Updated: 2025/01/14 15:09:02 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("ERROR: Unable to open file: ", 2);
		ft_putendl_fd(filename, 2);
	}
	return (fd);
}

char	*find_command_path(char *cmd, char **env)
{
	char	**paths = get_env_paths(env);
	char	*cmd_path = NULL;
	int		i = 0;

	while (paths && paths[i])
	{
		cmd_path = join_path(paths[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	free_split(paths);
	return (cmd_path);
}
