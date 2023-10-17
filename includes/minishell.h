/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/17 16:09:51 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

# define PROMPT "\e[1;32mMinishell~$ \e[0m"

// error messages
# define PIPE_AT_END "Error: pipe at the end"
# define REDIR_AT_END "Error: redirection at the end"
# define UNCLOSED_QOUTE "Error: unclosed quote"

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
	WRD,
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
	char	*infile;
	char	*outfile;
	char	*here_delemiter;
	int		fdin;
	int		fdout;
	int		stdin_backup;
	int		stdout_backup;
}			t_iofds;

typedef struct s_cmd
{
	char			*value;
	t_token			*token;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_cmds
{
	char			*cmd;
	char			**cmdarg;
	t_iofds			*iofd;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}					t_cmds;

typedef struct s_data
{
	char	*input;
	t_cmds	*cmds;
	t_token	*token; //is this the whole linked list of token nodes?
	char	**envi;
}			t_data;

// Error && other helper funcs
int					possible_error(char *input);
void				ft_error(char *err_msg, t_data **data);
char				*one_space_setter(char *str);
int					is_heredoc_append(char *str, int i, char c);
int					is_whitespace(char c);
int					is_operator(char c);
int					is_qoute(char c);
int					ft_whitespaces(char *str, int *index, char c);
char				**splitter(char *str);

// Double-linked list && Array funcs funcs
t_cmd				*ft_lstlast(t_cmd *lst);
void				ft_addnode_back(t_cmd **lst, t_cmd *node);
void				ft_clean_dl(t_cmd **dl);
int					ft_dlsize(t_cmd *lst);
int					arr_length(char **arr);
void				ft_clean_arr(char **argv);
void				ft_clean_data(t_data **data);

// launch funcs
int					start_program(t_data *data, char *input, char **envp);

//lexical analysis funcs
int					start_lexing(t_data *data, char *input, char **envp);
void				tokenize_cmd(t_token **lst, char *cmd);
int					add_tok_back(t_token **lst, t_token *token, int end_code);
t_token				*tokenize_mem(char *mem, int end_code);
void				ft_clean_tok_dl(t_token **dl);
int					ft_tokendl_size(t_token **lst);

// expansion funcs
int					start_expansion(t_data *data, char **envp);

// parsing funcs

// execution funcs

#endif