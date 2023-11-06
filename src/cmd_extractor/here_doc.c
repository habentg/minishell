/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:54:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/06 21:00:00 by hatesfam         ###   ########.fr       */
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

void	extract_here_doc(t_data *data, t_token **token, t_cmd **cmd_node)
{
	char	*content_line;
	char	*temp_file;
	int		tmp_fd;

	(void)data;
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

// char	*get_env_value(t_data *data, char *var_name)
// {
// 	t_env	*tmp;

// 	tmp = data->env_lst;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->key, var_name, ft_strlen(var_name)) == 0)
// 			return (tmp->value);
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// static char	*expand_variable_heredoc(t_data *data, char *read_line)
// {
// 	char	*exp_var;
// 	char	*exp_var_sub;
// 	char	*exp_var_join_tmp;
// 	char	*var_name;
// 	int		i;
// 	int		k;

// 	exp_var = NULL;
// 	i = 0;
// 	k = 0;
// 	while (read_line[i] && read_line[i] != '$')
// 		i++;
// 	if (i==0)
// 		exp_var_sub = ft_strdup("");
// 	else
// 		exp_var_sub = ft_substr(read_line, k, i - k);
// 	k = ++i;
// 	while (read_line[i] != '$' && is_whitespace(read_line[i]) == 0
// 		&& read_line[i] != '\0')
// 		i++;
// 	if (i == k)
// 		var_name = ft_strdup("$");
// 	else
// 		var_name = ft_substr(read_line, k, i - k);
// 	if (var_name)
// 	{
// 		if ( ft_strncmp_custom(var_name, "$", 1))
// 		exp_var_join_tmp = get_env_value(data, var_name);
// 		if (!exp_var_join_tmp)
// 			exp_var_join_tmp = ft_strdup("");
// 		exp_var = ft_strjoin(exp_var_join_tmp, exp_var_sub);
// 		free(var_name);
// 	}
// 	if (read_line[i] != '\0')
// 		var_name = ft_strjoin(exp_var, &read_line[i]);
// 	return (var_name);
// }


// // create a temp file (hidden preferabley)
// // write a content by reading from the standard INPUT untill the delimeter
// // set the current command infile to the temp file
// void	extract_here_doc(t_data *data, t_token **token, t_cmd **cmd_node)
// {
// 	char	*content_line;
// 	char	*temp_file;
// 	char	*extr_input;
// 	int		tmp_fd;

// 	(*cmd_node)->iofd->here_delemiter = ft_strdup((*token)->next->str);
// 	temp_file = generate_temp_file_name();
// 	tmp_fd = open(temp_file, O_CREAT | O_APPEND
// 		| O_RDWR, S_IRUSR | S_IWUSR);
// 	while (1)
// 	{
// 		content_line = readline("heredoc> ");
// 		if (ft_strncmp_custom(content_line, (*cmd_node)->iofd->here_delemiter,
// 			ft_strlen((*cmd_node)->iofd->here_delemiter)) == 0)
// 			break ;
// 		while(1)
// 		{
// 			if (ft_strchr(content_line, '$'))
// 			{
// 				extr_input = expand_variable_heredoc(data, content_line);
// 				ft_putendl_fd(extr_input, tmp_fd);
// 				free(extr_input);
// 			}
// 			else
// 			{
// 				ft_putendl_fd(content_line, tmp_fd);
// 				break ;
// 			}
// 		}
// 		free(content_line);
// 	}
// 	close(tmp_fd);
// 	(*cmd_node)->iofd->infile = (temp_file);
// 	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
// 	(*token) = (*token)->next->next;
// }

