/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/12 13:18:50 by hatesfam         ###   ########.fr       */
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

# define PIPE_AT_END "Error: pipe at the end"
# define REDIR_AT_END "Error: redirection at the end"
# define UNCLOSED_QOUTE "Error: unclosed quote"

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

typedef struct s_token
{
	char			*str;
	t_tokenType		type;
	int				len;
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
	t_token	*token;
	char	**env;
}	t_data;

typedef struct s_cmd
{
	char			*value;
	t_token			*token;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// input sanitization & helper funcs
int					check_input_cmd(t_cmd **cmd_lst, char *input);
char				*one_space_setter(char *str);
int					is_whitespace(char c);
int					is_operator(char c);
int					is_qoute(char c);
int					ft_whitespaces(char *str, int *index, char c);
int					possible_error(char *input, t_cmd **cmd_list);
void				ft_error(char *err_msg, t_cmd **cmd_list);

//lexical analysis && parsing funcs
void				tokenize_cmd(t_token **token_dlist, char *cmd);
void				tokenize_cmd(t_cmd **cmd_lst, char *pipe);
t_cmd				*ft_newnode(t_token *token, char *txt);

// doubly-linked link funcs
t_cmd				*ft_lstlast(t_cmd *lst);
void				ft_addnode_back(t_cmd **lst, t_cmd *node);
void				ft_clean_dl(t_cmd **dl);
int					ft_dlsize(t_cmd *lst);
#endif