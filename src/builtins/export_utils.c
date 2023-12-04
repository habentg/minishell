/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 02:44:13 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/19 10:28:49 by hatesfam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	bubble_sort_utils(char **sorted_envi, char **envi, int length)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	i = -1;
	j = -1;
	while (++i < length)
		sorted_envi[i] = ft_strdup(envi[i]);
	i = -1;
	while (++i < length - 1)
	{
		j = -1;
		while (++j < length - i - 1)
		{
			if (ft_strncmp(sorted_envi[j], sorted_envi[j + 1], \
				ft_strlen(sorted_envi[j + 1])) > 0)
			{
				tmp = sorted_envi[j];
				sorted_envi[j] = sorted_envi[j + 1];
				sorted_envi[j + 1] = tmp;
			}
		}
	}
}

char	**sorted_envi(char **envi)
{
	int		length;
	char	**sorted_envi;

	length = arr_length(envi);
	sorted_envi = (char **)ft_calloc(sizeof(char *), (length + 1));
	if (!sorted_envi)
		return (NULL);
	bubble_sort_utils(sorted_envi, envi, length);
	return (sorted_envi);
}

void	update_oldpwd(t_env *env_lst, char *oldpwd)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (ft_strncmp_custom(tmp->key, "OLDPWD", 6) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
			break ;
		}
		tmp = tmp->next;
	}
}

void	empty_oldpwd(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst;
	while (tmp)
	{
		if (ft_strncmp_custom(tmp->key, "OLDPWD", 6) == 0)
		{
			free(tmp->value);
			tmp->value = NULL;
		}
		tmp = tmp->next;
	}
}
