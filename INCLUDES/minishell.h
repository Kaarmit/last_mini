/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdakhlao <sdakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:38:11 by sdakhlao          #+#    #+#             */
/*   Updated: 2025/04/18 10:35:32 by sdakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/all.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_sig_exit;

typedef enum e_err_msg
{
	NOCMD = 0,
	ARGS,
	PATH,
	NOFILEDIR,
	EXPORT,
	EXPORT_OPT,
	UNSET,
	UNSET_OPT,
	EXIT_NB,
	UNCLEAR_REDIR,
	PERM_DENIED
}						t_err_msg;

typedef enum e_fsm
{
	NORMAL = 1,
	DOUBLE,
	SINGLE,
}						t_fsm;

typedef enum e_type
{
	ESPACE = 0,
	ARG = 1,
	EXP_ARG,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
}						t_type;

typedef enum e_io_type
{
	IO_IN = 1,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}						t_io_type;

typedef struct s_env
{
	char				*name;
	char				*content;
	int					printable;
	struct s_env		*prev;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	int					type;
	char				*token;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_io_chunk
{
	t_io_type			type;
	char				*path;
	char				**value;
	int					here_doc;
	struct s_io_chunk	*next;
	struct s_io_chunk	*prev;
}						t_io_chunk;

typedef struct s_chunk
{
	char				*cmd;
	pid_t				pid;
	char				**args;
	t_io_chunk			*io_handle;
	struct s_chunk		*prev;
	struct s_chunk		*next;
}						t_chunk;

typedef struct s_data
{
	t_token				*token;
	t_chunk				*chunk;
	t_env				*env;
	int					stdin;
	int					stdout;
	int					count;
	char				**envcpy;
	char				**tokens;
	char				*brut_input;
}						t_data;

typedef enum e_action
{
	UPDATE,
	RETRIEVE
}						t_action;

void					err_pipe(void);
void					err_fork(void);
char					*cplc2(char *s);
void					env(t_env **lst);
void					pwd(t_env **lst);
char					*joiner(char *s1);
void					set_signals(void);
int						is_dir(char *cmd);
int						is_dot(char *cmd);
char					*cut_dq(char *str);
void					free_ptr(void *ptr);
char					*str_after(char *s);
int						lexer(t_data *data);
char					**cpenv(char **env);
void					echo(t_chunk *chunk);
char					*str_before(char *s);
t_chunk					*lst_new_chunk(void);
int						builtin(t_data *data);
int						is_builtin(char *cmd);
int						count_tab(char **env);
void					redir(t_chunk *chunk);
// int						is_builtin(char *cmd);
t_env					*create_env_node(void);
void					pre_exec(t_data *data);
int						count(char *s, char c);
int						check_syntax(char *str);
void					free_lst(t_token *head);
void					syntax_error(char *str);
char					**malloc_free(char **tab);
char					*ft_strdup(const char *s);
void					clear_env_lst(t_env **lst);
t_token					*merge_args(t_token *head);
char					*two_first_char(char *cmd);
void					free_envcpy(char **envcpy);
void					heredoc_handler(int signal);
void					free_data_bis(t_data *data);
t_chunk					*init_chunk(t_chunk *chunk);
// void					free_data_exit(t_data *data);
void					free_data_exec(t_data *data);
char					**ft_spliit(char *s, char c);
void					ft_putstr_fd(char *s, int fd);
t_token					*remove_spaces(t_token *head);
int						init_io_chunk(t_chunk *chunk);
t_chunk					*lst_last_chunk(t_chunk *cmd);
char					**ft_split(char *s, char sep);
void					init_io_struct(t_io_chunk *io);
void					catch_sigint_exit(t_data *data);
int						syntax_precheck(t_token **head);
char					*ft_strjoin(char *s1, char *s2);
int						count_existing_args(char **args);
char					*expande_moi(char *s, char **env);
char					*get_path(t_data *data, char *cmd);
char					*create_word(char *start, int len);
int						ft_cd(t_chunk *chunk, t_data *data);
int						single_exit_s(int exit_s, int mode);
char					*find_path(char *cmd, t_data *data);
char					*error_message(int error, char *cmd);
void					lst_add_back(t_env **lst, t_env *cmd);
void					fill_env_lst(char **env, t_env **lst);
char					*is_double_quote(char **s, char quote);
int						init_lst(t_data *data, t_chunk *chunk);
char					*only_print_var(char *name, t_env **lst);
void					execs(t_data *data, t_chunk **chunk_lst);
int						quote_handle(char *s, char quote, int i);
int						dq_len(char **s, char *start, char quote);
int						add_end(t_token **head, t_token *new_node);
int						parse_tokens(t_data *data, t_token **tokens);
int						unset(char **args, t_env **lst, t_data *data);
int						export(t_env **lst, char **args, t_data *data);
void					exec_cmd(t_data *data, char **cmd, char **env);
void					replace_var(char *prev, char *new, t_env **lst);
int						handle_word(t_chunk **chunk, t_token **token_lst);
void					do_builtin(t_data *data, t_chunk *chunk, char *cmd);
void					lst_clear_chunk(t_chunk **lst, void (*del)(void *));
int						set_args(t_token **token_lst, t_chunk *current_chunk);
void					lst_add_back_chunk(t_chunk **lst_chunk, t_chunk *chunk);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					lstclear_io_list(t_io_chunk **io_list,
							void (*del)(void *));
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						add_more_args(t_token **token_lst,
							t_chunk *current_chunk, int old_size);
int						handle_redirection(t_chunk **chunk_lst,
							t_token **token_lst, t_type type);
void					create_node(t_data *data, char *token, int type,
							char **env);
int						copy_existing_args(char **new_args, char **args,
							int old_size);
int						add_new_args(char ***new_args, t_token **token_lst,
							int *i);
/* cd*/
void					change_oldpwd(t_env **lst, char **envcp, char *cwd);
char					*only_print_var(char *name, t_env **lst);
void					change_pwd(t_env **lst, char *path);
/**/
/*export*/
char					*get_var_name(char *var);
char					*get_var_content(char *var);
/**/
void					clean_program(t_data *data);
void					clean_program_exec(t_data *data);
char					*get_name(char *env);
void					free_data(t_data *data);

void					argless_export(t_env **lst);
t_env					**copy_env_to_array(t_env **lst, int len);
int						env_len(t_env *lst);
char					*malloc_quote_word(char **s);
char					*malloc_operator_word(char **s);
char					*malloc_word(char **s, char c);
int						skip_quotes(char *s, int i);
int						skip_operator(char *s, int i);
void					ft_exit(t_data *data);
int						is_pipe(char *str);
int						is_heredoc(char *str);
int						is_append(char *str);
int						is_trunc(char *str);
int						is_input(char *str);
int						is_exp_arg(char *str);
int						is_quoted_arg(char *str);
int						is_space(char *str);
int						skip_word(char *s, int i, char c);
char					**rewrite_env_tab(t_env *envlst);


#endif


