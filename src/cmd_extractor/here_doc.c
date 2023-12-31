/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:54:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/12/03 05:38:28 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_temp_file_name(void)
{
	static int	i;
	char		*temp_file_name;
	char		*i_temp;

	i_temp = ft_itoa(i);
	temp_file_name = ft_strjoin("/tmp/.hd_temp_file_", i_temp);
	if (i_temp)
		free(i_temp);
	i++;
	return (temp_file_name);
}

void	expand_heredoc_line(t_data *data, char *content, int tmp_fd)
{
	int	i;

	i = -1;
	while (content[++i])
	{
		if (content[i] != '$' || (content[i] == '$' && !content[i + 1]))
			ft_putchar_fd(content[i], tmp_fd);
		else if (content[i] == '$' && (content[i + 1] && content[i + 1] == '?'))
		{
			ft_putnbr_fd(data->exit_code, tmp_fd);
			i++;
		}
		else if (content[i] == '$' && (content[i + 1] && (content[i + 1] == '$' \
			|| (content[i + 1] == ' '))))
		{
			ft_putstr_fd("{PID}", tmp_fd);
			i++;
			i++;
		}
		else if (content[i] == '$' && (content[i + 1]))
		{
			i = for_real_expand(data, content, &i, tmp_fd);
			i--;
		}
	}
}

int	check_and_expand(t_data *data, t_cmd **cmd_node, \
	char *content_line, int tmp_fd)
{
	char	*trimmed_deli;

	trimmed_deli = ft_remove_quotes((*cmd_node)->iofd->here_delemiter, \
		count_len_unqouted((*cmd_node)->iofd->here_delemiter));
	if (!content_line || ft_strncmp_custom(trimmed_deli, content_line, \
		ft_strlen((*cmd_node)->iofd->here_delemiter)) == 0)
	{
		free(trimmed_deli);
		return (1);
	}
	if (is_heredoc_expandable(content_line) && \
		!ft_strchr((*cmd_node)->iofd->here_delemiter, '\"') && \
			!ft_strchr((*cmd_node)->iofd->here_delemiter, '\''))
	{
		expand_heredoc_line(data, content_line, tmp_fd);
	}
	else
		ft_putstr_fd(content_line, tmp_fd);
	ft_putchar_fd('\n', tmp_fd);
	free(trimmed_deli);
	return (0);
}

// create a temp file (hidden preferabley)
// write a content by reading from the standard INPUT untill the delimeter
// set the current command infile to the temp file
void	extract_here_doc(t_data *data, t_token **token, t_cmd **cmd_node)
{
	char	*temp_file;
	char	*content_line;
	int		tmp_fd;

	(*cmd_node)->iofd->here_delemiter = ft_strdup((*token)->next->str);
	temp_file = generate_temp_file_name();
	tmp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
	while (1)
	{
		init_signals();
		content_line = readline("heredoc> ");
		if (g_exit_status == OFF_HERE_DOC)
			break ;
		if (check_and_expand(data, cmd_node, content_line, tmp_fd))
			break ;
		free(content_line);
	}
	close(tmp_fd);
	heredoc_filename_fd_assign(cmd_node, temp_file);
}

void	ft_here_doc(t_data *data, t_token **token, t_cmd **cmd_node)
{
	g_exit_status = IN_HERE_DOC;
	extract_here_doc(data, token, cmd_node);
	if (g_exit_status == OFF_HERE_DOC)
	{
		while ((*token)->type != END)
			(*token) = (*token)->next;
	}
	else
		(*token) = (*token)->next->next;
}
