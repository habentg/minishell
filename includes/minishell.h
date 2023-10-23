/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/23 18:43:53 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <fcntl.h>    // for open
# include <unistd.h>   // for read, write, close
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

# define PROMPT "\e[1;32mMinishell~$ \e[0m"

//allocation error messages
# define ONESPACE_ALLOC_FAIL "Error: One space allocation failed"
# define TOKENDL_ALLOC_FAIL "Error: Token DL allocation failed"
# define CMD_ALLOC_FAIL "Error: CMD allocation failed"
# define FAILED_TO_DUPLICATE "Error: duplication failed in extract_cmdargs"

// error messages
# define TOKENIZE_FAIL "Error: Tokenization failure"
# define PIPE_AT_END "Error: pipe at the end"
# define REDIR_AT_END "Error: redirection at the end"
# define UNCLOSED_QOUTE "Error: unclosed quote"
# define OPERATOR_PIPE_ERROR "Error: syntax error near unexpected token '|'"
# define OPERATOR_ERROR "Error: syntax error near unexpected token '>'"

// exit status
// # define EXIT_SUCCESS 0

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
	WORD, // word = 0
	PIPE, // pipe = 1
	APPEND, // append = 2 >>
	TRUNC, // trunc = 3 >
	INPUT_REDIR, // input redirection = 4 <
	HERE_DOC, // here document = 5 <<
	VAR, // variable = 6
	END // end = 7
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

typedef struct s_cmd
{
	char			*cmd;
	char			**cmdarg;
	int				pipeout;
	t_iofds			*iofd;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_data
{
	char			*input;
	t_cmd			*cmd;
	t_token			*token;
	char			**envi;
}					t_data;

// Error && other helper funcs
int					possible_error(t_data **data);
int					operator_pipe_error(t_data *data);
void				ft_error(char *err_msg);
char				*one_space_setter(char *str);
int					is_heredoc_append(char *str, int i, char c);
int					is_whitespace(char c);
int					is_operator(char c);
int					is_qoute(char c);
int					ft_whitespaces(char *str, int *index, char c);
char				**splitter(char *str);
void				print_token(t_token *token);
void				print_cmd(t_cmd *cmd);

// Double-linked list && Array funcs funcs
int					arr_length(char **arr);
void				ft_clean_arr(char **argv);
void				ft_clean_data(t_data **data);

// launch funcs
int					launch_minishell(t_data *data, char **envp);
int					init_program(t_data *data);
int					init_data(t_data **data, char *input, char **envp);

//lexical analysis funcs
int					start_lexing(t_data *data);
int					tokenize_cmd(t_token **lst, char *cmd);
t_token				*last_mem(t_token *lst);
int					add_tok_back(t_token **lst, t_token *token);
t_token				*tokenize_mem(char *mem);
void				ft_clean_tok_dl(t_token **dl);
int					ft_tokendl_size(t_token **lst);

// expansion funcs
int					start_expansion(t_data *data);
int					is_expansion_possible(t_data *data, char *str);
t_quoteType			get_q_state(char *str, int end);
void				remove_quotes(t_data *data);

// cmd extraction funcs
int					start_cmd_extraction(t_data *data);

int					extract_word(t_token **token, t_cmd **cmd_lst);
int					extract_pipe(t_token **token, t_cmd **cmd_lst);
int					extract_trunc(t_token **token, t_cmd **cmd_lst);

t_cmd				*new_cmd(char *str);
t_cmd				*ft_lstlast(t_cmd *lst);
void				add_cmdnode_back(t_cmd **lst, t_cmd *node);
void				ft_clean_dl(t_cmd **dl);
int					ft_dlsize(t_cmd *lst);

t_iofds				*new_iofds(void);
// execution funcs

#endif