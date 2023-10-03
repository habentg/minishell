/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:55 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/03 05:02:19 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"

enum e_tokenType
{
	STR_L,
	OPRATOR,
	VAR
};

typedef struct s_token
{
	enum e_tokenType	type;
	char				*text;
	void				*next;
	void				*prev;
}	t_token;

char	*readline(const char *prompt);

#endif