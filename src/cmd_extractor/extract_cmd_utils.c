/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:51:34 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/20 18:03:28 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	this whole file is just to extract the command and its arguments
*/
int	count_cmdargs(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type == WORD)
	{
		token = token->next;
		i++;
	}
	return (i);
}

void	free_arglst(t_args **arg_lst)
{
	t_args	*tmp;

	while (*arg_lst)
	{
		tmp = (*arg_lst)->next;
		free((*arg_lst)->arg);
		free(*arg_lst);
		*arg_lst = tmp;
	}
	if (*arg_lst)
		free(*arg_lst);
}

void	print_arglst(t_args *arg_lst)
{
	t_args	*tmp;

	tmp = arg_lst;
	while (tmp)
	{
		printf("arg_lst : %s\n", tmp->arg);
		tmp = tmp->next;
	}
}

static int	extract_cmdargs(t_data *data, t_token **token, t_cmd **cmd_node)
{
	(void)data;
	if (!(*cmd_node)->cmd)
			(*cmd_node)->cmd = ft_strdup((*token)->str);
	while ((*token)->type != END && (*token)->type == WORD)
	{
		add_arglst_back(&(*cmd_node)->arg_lst, (*token)->str);
		(*token) = (*token)->next;
	}
	return (0);
}
// static int	extract_cmdargs(t_data *data, t_token **token, t_cmd **cmd_node)
// {
// 	int		count;
// 	int		i;

// 	i = 0;
// 	count = count_cmdargs(*token);
// 	(*cmd_node)->cmdarg = (char **)ft_calloc(sizeof(char *), (count + 1));
// 	if (!(*cmd_node)->cmdarg)
// 		return (1);
// 	while ((*token)->type != END && (*token)->type == WORD && i < count)
// 	{
// 		(*cmd_node)->cmdarg[i] = ft_strdup((*token)->str);
// 		if (!(*cmd_node)->cmdarg[i++])
// 			return (ft_error(data, FAILED_TO_DUPLICATE, 255), 1);
// 		if ((*token)->type == END)
// 			return (0);
// 		(*token) = (*token)->next;
// 	}
// 	return (0);
// }

int	extract_word(t_data *data, t_token **token, t_cmd **cmd_node)
{
	while ((*token)->type != END && (*token)->type == WORD)
	{
		if (extract_cmdargs(data, token, cmd_node))
			return (1);
		if (!(*token) || (*token)->type != WORD)
			return (0);
	}
	return (0);
}
