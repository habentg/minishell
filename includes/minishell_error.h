/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 18:50:22 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/01 19:31:29 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

//allocation/creation failure error messages
# define ONESPACE_ALLOC_FAIL "Error: One space allocation failed"

# define TOKENDL_ALLOC_FAIL "Error: Token DL allocation failed"

# define CMD_ALLOC_FAIL "Error: CMD allocation failed"

# define FAILED_TO_DUPLICATE "Error: duplication failed in extract_cmdargs"

# define TOKENIZE_FAIL "Error: Tokenization failure"

# define PIPE_MALLOC_ERROR "Error: PIPE allocation failed"

# define PIPE_FUNC_ERROR "Error: PIPE creation failed"

# define FD_DUP_FAILED "Error: Duplication of file descriptor failed"

// parsing messages
# define PIPE_AT_END "Error: pipe at the end"

# define REDIR_AT_END "Error: syntax error near unexpected token `newline'"

# define UNCLOSED_QOUTE "Error: unclosed quote"

# define OPERATOR_PIPE_ERROR "Error: syntax error near unexpected token '|'"

# define OPERATOR_ERROR_TRU "Error: syntax error near unexpected token '>'"

# define OPERATOR_ERROR_INP "Error: syntax error near unexpected token '<'"

# define OPERATOR_ERROR_APP "Error: syntax error near unexpected token '>>'"

# define OPERATOR_ERROR_HD "Error: syntax error near unexpected token '<<'"

// execution messages
# define FAILED_TO_OPEN_INPUT_FILE "Error: failed to find/open input file"

# define EXECVE_FAIL "Error: execve failed"

# define NO_FILE_DIR "No such file or directory"

# define PERMISSION_DENY "Permission denied"

# define CMD_NOT_FOUND "command not found"

# define IS_DIRCTRY "is a directory"

# define NVI "not a valid identifier"

#endif