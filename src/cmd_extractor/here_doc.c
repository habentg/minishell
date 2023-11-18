/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatesfam <hatesfam@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:54:44 by hatesfam          #+#    #+#             */
/*   Updated: 2023/11/18 05:06:43 by hatesfam         ###   ########.fr       */
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
			ft_putchar_fd(content[i++], tmp_fd);
			ft_putchar_fd(content[i], tmp_fd);
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
		exit (0);
	if (is_heredoc_expandable(content_line) && \
		!ft_strchr((*cmd_node)->iofd->here_delemiter, '\"') && \
			!ft_strchr((*cmd_node)->iofd->here_delemiter, '\''))
		expand_heredoc_line(data, content_line, tmp_fd);
	else
		ft_putstr_fd(content_line, tmp_fd);
	ft_putchar_fd('\n', tmp_fd);
	free(trimmed_deli);
	return (0);
}

// void	heredoc_signal(t_data *data, t_cmd *cmd_node, int sig)
// {
// 	if (sig == SIGINT)
// 		exitshell(data, cmd_node, 1);
		
// }

// void	handle_hd_signal(t_data *data, t_cmd *cmd_node)
// {
// 	signal(SIGINT, heredoc_signal);
// 	signal(SIGQUIT, heredoc_signal);
// }

// void heredoc_signal(int sig) {
//     if (sig == SIGINT) {
//         printf("\nReceived SIGINT in heredoc. Cleaning up...\n");
//         exit(1);
//     }
// }

// void	extract_here_doc(t_data *data, t_token **token, t_cmd **cmd_node)
// {
// 	char	*temp_file;
// 	char	*content_line;
// 	int		tmp_fd;

// 	(*cmd_node)->iofd->here_delemiter = ft_strdup((*token)->next->str);
// 	temp_file = generate_temp_file_name();
// 	tmp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
// 	signal(SIGINT, heredoc_signal);
// 		while (1)
// 		{
// 			content_line = readline("heredoc> ");
// 			if (check_and_expand(data, cmd_node, content_line, tmp_fd))
// 				break ;
// 			free(content_line);
// 		}
// 	close(tmp_fd);
// 	(*cmd_node)->iofd->infile = (temp_file);
// 	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
// 	(*token) = (*token)->next->next;
// }
// create a temp file (hidden preferabley)
// write a content by reading from the standard INPUT untill the delimeter
// set the current command infile to the temp file
// void	extract_here_doc(t_data *data, t_token **token, t_cmd **cmd_node)
// {
// 	char	*temp_file;
// 	char	*content_line;
// 	int		tmp_fd;

// 	(*cmd_node)->iofd->here_delemiter = ft_strdup((*token)->next->str);
// 	temp_file = generate_temp_file_name();
// 	tmp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
// 	while (1)
// 	{
// 		content_line = readline("heredoc> ");
// 		if (check_and_expand(data, cmd_node, content_line, tmp_fd))
// 			break ;
// 		free(content_line);
// 	}
// 	close(tmp_fd);
// 	(*cmd_node)->iofd->infile = (temp_file);
// 	(*cmd_node)->iofd->fdin = open((*cmd_node)->iofd->infile, O_RDONLY);
// 	(*token) = (*token)->next->next;
// }


/// here doc signal implementation

void heredoc_signal(int sig) {
    if (sig == SIGINT) {
        // Handle SIGINT in the heredoc process
        // For example, clean up resources and exit
        printf("\nReceived SIGINT in heredoc. Cleaning up...\n");
        exit(1);
    }
}

void extract_here_doc_child(t_data *data, t_token **token, t_cmd *cmd_node) {
    // Set up SIGINT signal handler in the child process
    signal(SIGINT, heredoc_signal);

    char *temp_file;
    char *content_line;
    int tmp_fd;

    cmd_node->iofd->here_delemiter = ft_strdup((*token)->next->str); // Set your delimiter
    temp_file = generate_temp_file_name();
    tmp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);

    while (1) {
        content_line = readline("heredoc> ");
        if (check_and_expand(data, &cmd_node, content_line, tmp_fd)) {
            break;
        }
        free(content_line);
    }

    // Close the temporary file
    close(tmp_fd);

    // Set infile and fdin in cmd_node
    cmd_node->iofd->infile = temp_file;
    cmd_node->iofd->fdin = open(cmd_node->iofd->infile, O_RDONLY);

    // Exit the child process
    exit(0);
}

void extract_here_doc_parent(t_data *data, t_token **token, t_cmd **cmd_node) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        // Handle fork error
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        extract_here_doc_child(data, token, *cmd_node);
    } else {
        // Parent process
        // Wait for the child process to finish
        waitpid(pid, &status, 0);

        // Handle the status if needed
		if (WTERMSIG(status))
			sig_handler();

        // Move to the next token
        (*token) = (*token)->next->next;
    }
}

// Example usage
// Call this function from your main program
void run_extract_here_doc(t_data *data, t_token **token, t_cmd **cmd_node) {
    extract_here_doc_parent(data, token, cmd_node);
}