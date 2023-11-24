/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:42:43 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/24 18:27:35 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

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

// where am I enumuration
typedef enum e_whereAmI
{
	IN_MINI = 10,
	IN_CMD = 20,
	IN_HERE_DOC = 30,
	OFF_HERE_DOC = 1,
	CTRL_C = 130,
}			t_whereAmI;

// qoute state enumuration for lexical analysis
typedef enum e_quoteType
{
	NONE,
	SINGLE,
	DOUBLE
}			t_quoteType;

// token type enumuration for lexical analysis
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
	int				was_mpty_before;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

// struct for input/output fds
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

// struct for cmd arguments args [ls -l -a]
typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
}					t_args;

// struct for each cmd node
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

// struct for env variables {easy to manuplate than array of strings}
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// struct for our general data (has everything we need to run the shell)
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

#endif