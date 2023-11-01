/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:54:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/01 10:16:05 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_temp_file_name(void)
{
	static int	i;
	char		*temp_file_name;

	temp_file_name = ft_strjoin("../../.hd_temp_file_", ft_itoa(i++));
	return (temp_file_name);
}

// create a temp file (hidden preferabley)
// write a content by reading from the standard INPUT untill the delimeter
// set the current command infile to the temp file
void	extract_here_doc(t_token **token, t_cmd **cmd_node)
{
	char	*content_line;
	char	*temp_file;
	int		tmp_fd;

	(*cmd_node)->iofd->here_delemiter = ft_strdup((*token)->next->str);
	temp_file = generate_temp_file_name();
	tmp_fd = open(temp_file, O_CREAT | O_APPEND \
		| O_RDWR, S_IRUSR | S_IWUSR);
	while (1)
	{
		content_line = readline("heredoc> ");
		if (ft_strncmp_custom(content_line, (*cmd_node)->iofd->here_delemiter, \
			ft_strlen((*cmd_node)->iofd->here_delemiter)) == 0)
			break ;
		ft_putendl_fd(content_line, tmp_fd);
		free(content_line);
	}
	close(tmp_fd);
	(*cmd_node)->iofd->infile = (temp_file);
	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
	(*token) = (*token)->next->next;
}
