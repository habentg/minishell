/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_iofds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:45:43 by hatesfam          #+#    #+#             */
/*   Updated: 2024/04/02 01:05:59 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_iofds	*new_iofds(void)
{
	t_iofds	*iofds;

	iofds = (t_iofds *)malloc(sizeof(t_iofds));
	if (!iofds)
		return (NULL);
	iofds->infile = NULL;
	iofds->outfile = NULL;
	iofds->fdin = -1;
	iofds->fdout = -1;
	iofds->here_delemiter = NULL;
	iofds->stdin_backup = -1;
	iofds->stdout_backup = -1;
	return (iofds);
}

char	*get_env_value(t_data *data, char *var_name)
{
	t_env	*tmp;

	tmp = data->env_lst;
	while (tmp)
	{
		if (ft_strncmp_custom(tmp->key, var_name, ft_strlen(var_name)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
