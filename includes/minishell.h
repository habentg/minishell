/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/21 14:51:13 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

# include "libft/libft.h"

# define PROMPT "\e[1;32mሚ  ኒ ሸ ል $▸ \e[0m"

//allocation error messages
# define ONESPACE_ALLOC_FAIL "Error: One space allocation failed"
# define TOKENDL_ALLOC_FAIL "Error: Token DL allocation failed"
# define CMD_ALLOC_FAIL "Error: CMD allocation failed"
# define FAILED_TO_DUPLICATE "Error: duplication failed in extract_cmdargs"
# define PIPE_MALLOC_ERROR "Error: PIPE allocation failed"
# define PIPE_FUNC_ERROR "Error: PIPE creation failed"
# define FD_DUP_FAILED "Error: Duplication of file descriptor failed"
# define EXECVE_FAIL "Error: execve failed"
# define NO_FILE_DIR "No such file or directory"
# define PERMISSION_DENY "Permission denied"
# define CMD_NOT_FOUND "command not found"
# define IS_DIRCTRY "is a directory"

// error messages
# define TOKENIZE_FAIL "Error: Tokenization failure"
# define PIPE_AT_END "Error: pipe at the end"
# define REDIR_AT_END "Error: syntax error near unexpected token `newline'"
# define UNCLOSED_QOUTE "Error: unclosed quote"
# define OPERATOR_PIPE_ERROR "Error: syntax error near unexpected token '|'"
# define OPERATOR_ERROR_TRU "Error: syntax error near unexpected token '>'"
# define OPERATOR_ERROR_INP "Error: syntax error near unexpected token '<'"
# define OPERATOR_ERROR_APP "Error: syntax error near unexpected token '>>'"
# define OPERATOR_ERROR_HD "Error: syntax error near unexpected token '<<'"

// FILE DESCRIPTORS & FILE ACCESS ERRORS
# define FAILED_TO_OPEN_INPUT_FILE "Error: failed to find/open input file"

// exit status
int	g_exit_status;

// qoute state struct
typedef enum e_quoteType
{
	NONE,
	SINGLE,
	DOUBLE
}			t_quoteType;

// token type struct
typedef enum e_tokenType
{
	WORD,
	PIPE,
	APPEND,
	TRUNC,
	INPUT_REDIR,
	HERE_DOC,
	VAR,
	END
}			t_tokenType;

// token node struct
typedef struct s_token
{
	char			*str;
	t_tokenType		type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_iofds
{
	char			*infile;
	char			*outfile;
	char			*here_delemiter;
	int				fdin;
	int				fdout;
	int				stdin_backup;
	int				stdout_backup;
}					t_iofds;

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

typedef struct s_cmd
{
	char			*cmd;
	char			**cmdarg;
	t_args			*arg_lst;
	int				pipeout;
	t_iofds			*iofd;
	int				*pipe_fd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*input;
	t_cmd			*cmd_lst;
	t_token			*token;
	char			**envi;
	char			**path;
	t_env			*env_lst;
	char			*cwd;
	int				exit_code;
	pid_t			ch_pid;
}					t_data;

// launch funcs
int					launch_minishell(t_data *data);
int					init_program(t_data *data);
int					init_data(t_data **data, char **envp);
int					init_env_path(t_data **data, char **envp);
void				add_env_back(t_data *data, char **env_node_arr);
int					create_env_lst(t_data **data);
t_env				*new_env_node(char *key, char *value);
int					ft_env_lsize(t_env *lst);
void				shlvl_increment(t_data *data, int inc_dec);

//lexical analysis funcs
int					start_lexing(t_data *data);
int					tokenize_cmd(t_token **lst, char *cmd);
t_token				*last_mem(t_token *lst);
int					add_tok_back(t_token **lst, t_token *token);
t_token				*tokenize_mem(char *mem);
int					ft_tokendl_size(t_token **lst);

// var expansion funcs
int					start_expansion(t_data *data);
bool				is_expansion_possible(char *str, int t_type);
void				pid_replacer(t_token *token);
t_quoteType			get_q_state(char *str, int end);
void				remove_quotes(t_data *data);
void				expand_variable(t_data *data, t_token *token);
int					count_len_unqouted(char *str);
char				*ft_remove_quotes(char *str, int len);
int					replace_var(t_data *data, t_token \
	*token, char *var_name, int *index);
char				*var_not_found(char *b_var, char *a_var);

// cmd extraction funcs
int					start_cmd_extraction(t_data *data);
int					cmd_node_construction(t_data *data, t_token **token, \
	t_cmd **cmd_lst);
int					extract_word(t_data *data, \
	t_token **token, t_cmd **cmd_node);
void				extract_pipe(t_token **token, t_cmd **cmd_lst);
void				extract_trunc(t_token **token, t_cmd **cmd_node);
int					extract_input_redir(t_token **token, t_cmd **cmd_node);
void				extract_here_doc(t_data *data, t_token **token, \
	t_cmd **cmd_node);
int					is_heredoc_expandable(char *str);
int					for_real_expand(t_data *data, char *content, int *i, \
	int tmp_fd);
void				extract_append(t_token **token, t_cmd **cmd_node);
t_cmd				*new_cmd(void);
t_cmd				*ft_lstlast(t_cmd *lst);
void				add_cmdnode_back(t_cmd **lst, t_cmd *node);
int					ft_dlsize(t_cmd *lst);
t_iofds				*new_iofds(void);
int					iofd_validity(t_cmd *cmd_node, t_iofds *iofd);
int					check_cmd_validity(t_data *data, t_cmd **cmd_node);
int					remove_prev_iofdins(t_cmd **cmd_node, t_token **token);
int					remove_prev_iofdouts(t_cmd **cmd_node, t_token **token);
int					is_token_operator(t_token *token);
int					check_after_del(t_data *data, t_token *token);
		// for the args - linked list
t_args				*args_node(char *arg);
int					add_arglst_back(t_args **lst, char *arg);
int					ft_arglstsize(t_args **lst);
t_args				*last_arg(t_args *lst);
char				**arr_from_arglst(t_args *arg_lst);
void				print_arglst(t_args *arg_lst);
void				free_arglst(t_args **arg_lst);
void				update_cmd_args(t_cmd *cmd_node);
// execution funcs
int					start_execution(t_data *data);
char				*get_path(char **envp, char *key);
int					create_pipes(t_data *data, t_cmd *cmd);
bool				is_builtin_cmd(t_cmd *cmd_node);
int					exec_builtin_cmd(t_cmd *cmd_node, t_data *data);
int					pre_exec_checks(t_data *data, t_cmd *cmd_node);
char				**ft_split_custom(char *str);
int					fork_wait(t_data *data);
// void 				run_extract_here_doc(t_data *data, 
	// t_token **token, t_cmd **cmd_node);
			// builtins
int					handle_pwd(t_data *data);
int					handle_echo(t_cmd *cmd_node);
int					handle_exit(t_data *data, t_cmd *cmd_node);
int					handle_export(t_data *data, t_cmd *cmd_node);
int					handle_cd(t_cmd *cmd_node, t_data *data);
void				update_envi(t_data *data);
void				env_lst_to_arr(t_data *data);
int					handle_unset(t_data *data, t_cmd *cmd_node);
int					handle_env(t_data *data, t_cmd *cmd_node);
int					valid_key_check(char *key, int unset_flag);
void				remove_env_node(t_env **env_lst, char *key_re);
void				update_oldpwd(t_env *env_lst, char *oldpwd);
void				empty_oldpwd(t_env *env_lst);
			// fd related
void				dup_pipe_fds(t_cmd **cmd_lst, t_cmd **cmd_node);
void				reset_std_fds(t_cmd **cmd_node);
void				backup_std_fds(t_cmd **cmd_node);
void				close_cmd_fds(t_cmd **cmd_node);
void				close_used_pipe_fds(t_cmd **cmd_lst, t_cmd **cmd_node);
void				close_unused_pipe_fds(t_cmd **cmd_lst, t_cmd *cmd_node);
int					set_redirections(t_data *data, t_iofds *iofd);
void				reset_stdio(t_iofds *iofds);
void				exitshell(t_data *data, t_cmd *cmdnode, int excode);
void				close_open_fds(t_cmd *cmd_lst, int exc_ended);
// Error && other helper funcs
int					possible_error(t_data **data);
int					operator_pipe_error(t_data *data);
void				ft_error(t_data *data, char *err_msg, int exit_status);
char				*one_space_setter(char *str);
int					is_heredoc_append(char *str, int i, char c);
int					is_whitespace(char c);
int					is_operator(char c);
int					is_qoute(char c);
int					ft_whitespaces(char *str, int *index, char c);
char				**splitter(char *str);
void				print_token_lst(t_token *token);
void				print_cmd_lst(t_cmd *cmd);
int					ft_strncmp_custom(const char *str1, \
	const char *str2, size_t n);
void				print_arr(char **arr);
void				print_env_lst(t_data *data);
		// err printer
void				display_error_2(char *s1, char *s2, char *s3);
void				display_error(char *s1, char *s2);
long long			ft_atol(char *str);
// cleaning funcs
void				ft_clean_arr(char **argv);
void				ft_clean_tok_dl(t_token **lst);
void				ft_delone_token(t_token *lst);
void				ft_lst_clear_cmd(t_cmd **lst);
void				ft_free_iofile(t_iofds *iofiles);
int					arr_length(char **arr);
void				ft_clean_arr(char **argv);
void				ft_clean_data(t_data **data);
void				ft_clean_data_done(t_data **data, int code);
void				free_cmdnode(t_cmd *cmd);
void				free_env_lst(t_data *data);
char				*get_env_value(t_data *data, char *var_name);
t_env				*last_env_node(t_env *lst);
char				**sorted_envi(char **envi);

// signal handler
void				sig_handler(void);
void				child_signals(t_cmd *cmd);
char				**ft_split_custom(char *str);

void				set_iofds(t_data *data, t_iofds *iofds);

#endif