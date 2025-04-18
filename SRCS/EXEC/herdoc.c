#include "../INCLUDES/minishell.h"

int	is_valid_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*strjoin_f(char *s1, char *s2)
{
	char	*join;
	size_t	len;
	size_t	i;
	size_t	j;

	if (s1 && !s2)
		return (free(s1), NULL);
	if (!s1 || !s2)
		return (NULL);
	len =  ft_strlen(s1) + ft_strlen(s2) +1;
	join = ft_calloc(len, sizeof(char));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j= 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	return (free(s1), free(s2), join);
}

int	heredoc_expander_w(char *str, int i, int fd, t_data *data)
{
	int		start;
	char	*tmp;
	char	*tmp2;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(single_exit_s(0, RETRIEVE), fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = ft_substr(str, start, i);
		tmp2 = only_print_var(tmp, &data->env);
		free (tmp);
		if (tmp2)
			ft_putstr_fd(tmp2, fd);
	}
	return (i);
}

void	heredoc_expander(char *str, int fd, t_data *data)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '$')
			i += heredoc_expander_w(str, i, fd, data);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}

char	*cleaned_heredoc_delim(char *res)
{
	char	*cleaned;
	int		i;
	int		start;
	char	*sub;

	sub = NULL;
	i = 0;
	cleaned = ft_strdup("");
	while (res[i])
	{
		if (res[i] == '"' || res[i] == '\'')
			i++;
		start = i;
		while (res[i] && !(res[i] == '"' || res[i] == '\''))
			i++;
		sub = ft_substr(res, start, i - start);
		cleaned = strjoin_f(cleaned, sub);
	}
	return (free(res), cleaned);
}

char	*handle_dollar_delim(char *path, int *i)
{
	if ((path[*i + 1] == '"' || path[*i + 1] == '\''))
	{
		if (*i == 0)
		{
			(*i)++;
			return (ft_strdup(""));
		}
		else if (path[*i - 1] && path[*i - 1] != '$')
		{
			(*i)++;
			return (ft_strdup(""));
		}
	}
	(*i)++;
	return (ft_strdup("$"));
}

char	*expand_heredoc_delim(char *path)
{
	char	*res;
	char	*sub;
	int		start;
	int		i;

	res = ft_strdup("");
	sub = NULL;
	i = 0;
	while (path[i])
	{
		if (path[i] == '$')
			res = strjoin_f(res, handle_dollar_delim(path, &i));
		start = i;
		while (path[i] && !(path[i] == '$'))
			i++;
		sub = ft_substr(path, start, i - start);
		res = strjoin_f(res, sub);
	}
	res = cleaned_heredoc_delim(res);
	return (res);
}

int	ft_isdelim(char *delim, char *str)
{
	while (*str)
	{
		if (*delim == '"' || *delim =='\'')
		{
			delim++;
			continue ;
		}
		else if (*str == *delim)
		{
			str++;
			delim++;
		}
		else
			return (0);
	}
	while (*delim == '"' || *delim =='\'')
		delim++;
	return (!*delim);
}

void	ignore_it(t_chunk *chunk, t_io_chunk *io)
{
	t_io_chunk	*io_prev;
	t_chunk		*prev_chunk;

	prev_chunk = chunk->prev;
	while (prev_chunk)
	{
		if (prev_chunk->io_handle && prev_chunk->io_handle->type == IO_HEREDOC)
			close(prev_chunk->io_handle->here_doc);
		prev_chunk = prev_chunk->prev;
	}
	io_prev = io->prev;
	while (io_prev)
	{
		if (io_prev->type == IO_HEREDOC)
			close(io_prev->here_doc);
		io_prev = io_prev->prev;
	}
}

void	get_delim(t_io_chunk *io)
{
	signal(SIGINT, heredoc_handler);
	io->value = malloc(sizeof(char *) * 2);
	if (!io->value)
		return ;
	io->value[0] = ft_strdup(io->path);
	io->value[1] = NULL;
	return ;
}

void	come_heredoc(t_data *data, t_io_chunk *io, int fd[2])
{
	char	*line;
	char	*quotes;

	get_delim(io);
	quotes = io->path;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		catch_sigint_exit(data);
		if (!line)
			break ;
		if (ft_isdelim(io->value[0], line))
			break ;
		if (!*quotes)
			heredoc_expander(line, fd[1], data);
		else
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
		}
		free(line);
	}
	(clean_program_exec(data), close(fd[1]), close(fd[0]), exit(0));
}

int	quit_here(int fd[2], int *pid)
{
	waitpid(*pid, pid, 0);
	close(fd[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (single_exit_s(130, UPDATE), 1);
	return (0);
}

int	init_heredoc(t_data *data, t_chunk *chunk)
{
	t_io_chunk	*io;
	int			fd[2];
	int			pid;

	io = chunk->io_handle;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			ignore_it(chunk, io);
			pipe(fd);
			signal(SIGINT, SIG_IGN);
			pid = fork();
			if (!pid)
				come_heredoc(data, io, fd);
			if (quit_here(fd, &pid))
				return (0);
			io->here_doc = fd[0];
			close(io->here_doc);
		}
		else
		{
			io->value[0] = ft_strdup(io->path);
			io->value[1] = NULL;
		}
		io = io->next;
	}
	return (1);
}

int	init_lst(t_data *data, t_chunk *chunk)
{
	if (!chunk)
		return (0);
	if (chunk->next)
	{
		if (!init_heredoc(data, chunk))
			return (0);
		return (init_lst(data, chunk->next));
	}
	else
	{
		if (!init_heredoc(data, chunk))
			return (0);
	}
	return (1);
}

