/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:12:27 by hatesfam          #+#    #+#             */
/*   Updated: 2023/10/25 13:38:34 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// str len - var_len + envp_len(after equal) + 1 (for null termi) -> malloc this one (free the old one first)
// our final token->str == characters before $ + envp_len(after equal) + characters after var_name + '\0'

// void	search_n_replace()
// {

// }

int	replace_var(t_data *data, t_token *token, char *var_name, int var_len, int *index)
{
	int		i;
	int		k;
	int		remain_len;
	int		envp_len;
	char	*tmp;

	i = -1;
	k = 0;
	remain_len = 0;
	envp_len = 0;
	tmp = NULL;
	while (data->envi[++i])
	{
		if (ft_strncmp(data->envi[i], var_name, var_len) == 0)
		{
			remain_len = ft_strlen(token->str) - var_len - 1;
			envp_len = ft_strlen(data->envi[i]) - var_len - 1;
			tmp = (char *)malloc(sizeof(char) * (remain_len + envp_len + 1));
			while (token->str[k])
			{
				if (token->str[k] == '$' && get_q_state(token->str, k) \
					!= SINGLE)
					break ;
				tmp[k] = token->str[k];
				k++;
			}
			remain_len = k + var_len + 1;
			while (data->envi[i][++var_len])
				tmp[k++] = data->envi[i][var_len];
			*index = k;
			while (token->str[remain_len])
				tmp[k++] = token->str[remain_len++];
			tmp[k] = '\0';
			free(token->str);
			token->str = tmp;
		}
	}
	return (*index);
}

static void	expand_variable(t_data *data, t_token *token)
{
	char	*var_name;
	int		i;
	int		k;

	var_name = NULL;
	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$' && get_q_state(token->str, i) != SINGLE)
		{
			k = ++i;
			if (!token->str[i])
				break ;
			while (token->str[i] && !is_whitespace(token->str[i]) && \
				token->str[i] != '$' && !is_operator(token->str[i]) \
				&& !is_qoute(token->str[i]))	
				i++;
			if ((i - k) > 0)
			{
				var_name = ft_substr(token->str, k, i - k);
				i = replace_var(data, token, var_name, i - k, &i);
				free(var_name);
			}
		}
		else
			i++;
	}
}

static int	init_var_expansion(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			if (is_expansion_possible(data, tmp->str) != 0)
			{
				if (is_expansion_possible(data, tmp->str) == 2)
					return (1);
				expand_variable(data, tmp);
				tmp->type = WORD;
			}
			else
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
	return (0);
}

static void	check_for_var(t_token **token_lst)
{
	t_token	*tmp;

	tmp = *token_lst;
	while (tmp)
	{
		if (strchr(tmp->str, '$'))
			tmp->type = VAR;
		tmp = tmp->next;
	}
}

int	start_expansion(t_data *data)
{
	check_for_var(&data->token);
	if (init_var_expansion(data))
		return (1);
	remove_quotes(data);
	// print_token(data->token);
	return (0);
}
