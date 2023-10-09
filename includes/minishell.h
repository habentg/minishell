/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/09 09:57:21 by hatesfam         ###   ########.fr       */
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
// error defs
# define PIPE_AT_END "Error: pipe at the end"
# define REDIR_AT_END "Error: redirection at the end"
# define UNCLOSED_QOUTE "Error: unclosed quote"

typedef enum e_tokenType
{
	WRD,
	CMD_OPT,
	PIPE='|',
	APPEND,
	TRUNC='>',
	INPUT_REDIR='<',
	HERE_DOC,
	VAR='$',
	F_FILE
}			t_tokenType;

typedef enum s_qt_state
{
	IN_S_QOUTES,
	IN_D_QOUTES,
	NORMAL
}			t_qt_state;

typedef struct s_token
{
	t_tokenType	*type;
	t_qt_state	*state;
	int			len;
}				t_token;

typedef struct s_cmd
{
	char			*value;
	t_token			*token;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// input sanitization & helper funcs
int					check_input_cmd(t_cmd **cmd_lst, char *input);
int					is_whitespace(char c);
int					is_operator(char c);
int					ft_whitespaces(char *str, int *index);
int					possible_error(char *input);
void				ft_error(char *err_msg, t_cmd **cmd_list);

//lexical analysis, parsing and doubly-linked link funcs
void				parse(t_cmd **cmd_lst, char *cmd);
t_cmd				*ft_newnode(t_token *token, char *txt);
t_cmd				*ft_lstlast(t_cmd *lst);
void				ft_addnode_back(t_cmd **lst, t_cmd *node);
#endif