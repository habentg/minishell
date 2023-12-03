/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:53:51 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/03 05:38:33 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredoc_expandable(char *str)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '$')
				return (0);
			else if (str[i + 1])
				return (1);
		}
		i++;
	}
	return (0);
}

char	*get_var_name(char *content, int *i)
{
	int	k;

	k = *i;
	while (content[*i] && (content[*i] != '$' && content[*i] != ' ' \
		&& !is_qoute(content[*i]) && !is_operator(content[*i])))
		(*i)++;
	return (ft_substr(content, k, *i - k));
}

int	for_real_expand(t_data *data, char *content, int *i, int tmp_fd)
{
	char	*var_name;
	char	*exp_var;

	(*i)++;
	var_name = get_var_name(content, i);
	exp_var = get_env_value(data, var_name);
	if (!exp_var)
		exp_var = NULL;
	ft_putstr_fd(exp_var, tmp_fd);
	free(var_name);
	return (*i--);
}

void	heredoc_filename_fd_assign(t_cmd **cmd_node, char *temp_file)
{
	if ((*cmd_node)->iofd->infile)
	{
		if ((*cmd_node)->iofd->fdin != -2)
			close((*cmd_node)->iofd->fdin);
		free((*cmd_node)->iofd->infile);
	}
	(*cmd_node)->iofd->infile = (temp_file);
	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
}
