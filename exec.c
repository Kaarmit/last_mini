
int	is_dir(char *cmd)
{
	DIR		*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (1);
	}
	closedir(dir);
	return (0);
}

int	is_dot(char *cmd)
{
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		return (1);
	}
	return (0);
}

void	redir_in(t_io_chunk *io)
{
	int	fdi;

	if (!io->path)
	{
		printf("no infile\n");
		return ;
	}
	fdi = open(io->path, O_RDONLY);
	if (fdi == -1)
	{
		perror("open infile");
		exit(1);
	}
	dup2(fdi, STDIN_FILENO);
	close(fdi);
}

void	redir_out(t_io_chunk *io)
{
	int	fdo;

	if (!io->path)
	{
		printf("no infile\n");
		return ;
	}
	fdo = open(io->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdo == -1)
	{
		perror("open outfile");
		exit(1);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
}

void	redir_append(t_io_chunk *io)
{
	int	fdo;

	if (!io->path)
	{
		printf("no infile\n");
		return ;
	}
	fdo = open(io->path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fdo == -1)
	{
		perror("open append");
		exit(1);
	}
	dup2(fdo, STDOUT_FILENO);
	close(fdo);
}

void	redir(t_chunk *chunk)
{
	t_io_chunk	*io;

	io = chunk->io_handle;
	if (!io)
		return ;
	while (io)
	{
		if (io->type == IO_IN)
			redir_in(io);
		else if (io->type == IO_OUT)
			redir_out(io);
		else if (io->type == IO_APPEND)
			redir_append(io);
		io = io->next;
	}
	return ;
}

void	err_pipe(void)
{
	write(2, "pipe failed\n", 12);
	exit(127);
}

void	err_fork(void)
{
	write(2, "fork failed\n", 12);
	exit(127);
}

char	*find_path(char *cmd, t_data *data)
{
	int		i;
	char	*part_path;
	char	**paths;
	char	*path;

	i = 0;
	part_path = only_print_var("PATH", &data->env);
	if (!part_path)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	paths = ft_split(part_path, ':');
	free(part_path);
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
		{
			i = -1;
			while (paths[++i])
				free(paths[i]);
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	return (free(paths), NULL);
}

void	exec_cmd(t_data *data, char **cmd, char **env)
{
	char	*path;

	if (!cmd || !cmd[0])
		return ;
	path = find_path(cmd[0], data);
	if (!path)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		exit(127) ;
	}
	if (execve(path, cmd, env) == -1)
		exit(127);
}

void	process(t_data *data, pid_t pid1)
{
	int	status;
	if (pid1 == 0)
	{
		if (is_dot(data->chunk->cmd))
			return (free_data_exec(data));
		if (is_dir(data->chunk->cmd))
			return (free_data_exec(data));
		redir(data->chunk);
		exec_cmd(data, data->chunk->args, data->envcpy);
	}
	waitpid(pid1, &status, 0);
	// close(data->stdin);
	// close(data->stdout);
	return ;
}

void	exec(t_data *data)
{
	pid_t	pid111;

	if (!data->chunk->args)
	{
		data->stdin = dup(0);
		data->stdout = dup(1);
		redir(data->chunk);
		dup2(data->stdin, STDIN_FILENO);
		dup2(data->stdout, STDOUT_FILENO);
		close(data->stdin);
		close(data->stdout);
		return ;
	}
	else if (is_builtin(data->chunk->cmd))
	{
		data->stdin = dup(0);
		data->stdout = dup(1);
		redir(data->chunk);
		do_builtin(data, data->chunk, data->chunk->cmd);
		dup2(data->stdin, STDIN_FILENO);
		dup2(data->stdout, STDOUT_FILENO);
		close(data->stdin);
		close(data->stdout);
		return ;
	}
	else
	{
		pid111 = fork();
		if (pid111 == -1)
			err_fork();
		process(data, pid111);
	}
	return ;
}

void	pre_exec(t_data *data)
{
	t_chunk	*chunk;

	chunk = data->chunk;
	if (chunk && !(chunk->next))
		exec(data);
	else
		execs(data, &data->chunk);
}

static void	ft_close_all(int fd[3])
{
	char	buf;
	int		i;

	i = 4;
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	while (i < 150)
	{
		if (read(i, &buf, 0) != -1)
			close(i);
		i++;
	}
}

void	processs(t_data *data, t_chunk *chunk, int fd[3])
{
	if (!chunk->prev)
		dup2(fd[1], STDOUT_FILENO);
	if (!chunk->next)
		dup2(fd[2], STDIN_FILENO);
	else if (chunk->next && chunk->prev)
	{
		dup2(fd[2], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	ft_close_all(fd);
	if (!chunk->args)
	{
		redir(chunk);
		close(data->stdin);
		close(data->stdout);
		free_data_exec(data);
		rl_clear_history();
		exit(0);
	}
	else if (is_builtin(chunk->cmd))
	{
		redir(chunk);
		do_builtin(data, chunk, chunk->cmd);
		redir(chunk);
		close(data->stdin);
		close(data->stdout);
		free_data_exec(data);
		rl_clear_history();
		exit(0);
	}
	if (is_dot(data->chunk->cmd))
		return (free_data_exec(data));
	if (is_dir(data->chunk->cmd))
		return (free_data_exec(data));
	redir(chunk);
	exec_cmd(data, chunk->args, data->envcpy);
}

void	waitit(t_data *data)
{
	t_chunk	*chunk;

	chunk = (data->chunk);
	while (chunk)
	{
		waitpid(chunk->pid, NULL, 0);
		chunk = chunk->next;
	}
}

void	swap_pipes(int fd[3])
{
	dup2(fd[0], fd[2]);
	close(fd[0]);
	close(fd[1]);
}

void	execs(t_data *data, t_chunk **chunk_lst)
{
	int		fd[3];
	t_chunk	*chunk;

	chunk = (*chunk_lst);
	data->stdin = dup(STDIN_FILENO);
	data->stdout = dup(STDOUT_FILENO);
	fd[2] = dup(STDIN_FILENO);
	while (chunk)
	{
		if (pipe(fd) != 0)
			err_pipe();
		chunk->pid = fork();
		if (chunk->pid == -1)
			err_fork();
		if (!chunk->pid)
			processs(data, chunk, fd);
		swap_pipes(fd);
		close(data->stdin);
		close(data->stdout);
		chunk = chunk->next;
	}
	close(fd[2]);
	waitit(data);
}