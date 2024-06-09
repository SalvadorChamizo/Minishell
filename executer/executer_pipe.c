/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/09 19:17:04 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

void	ft_pipe_middle(t_ast *ast, t_minishell *minishell, int pipe_in[2], int pipe_out[2])
{
	//dup2(minishell->stdin_fd, STDIN_FILENO);
	//dup2(minishell->stdout_fd, STDOUT_FILENO);
	close(pipe_in[1]);
	dup2(pipe_in[0], STDIN_FILENO);
	close(pipe_out[0]);
	dup2(pipe_out[1], STDOUT_FILENO);
	close(pipe_in[0]);
	close(pipe_out[1]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	//dup2(minishell->stdin_fd, STDIN_FILENO);
	//dup2(minishell->stdout_fd, STDOUT_FILENO);
	close(pipefd[0]);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell, int pipefd[2])
{
	//dup2(minishell->stdin_fd, STDIN_FILENO);
	//dup2(minishell->stdout_fd, STDOUT_FILENO);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	ft_simple_command2(ast, minishell);
	//dup2(original_stdin, STDIN_FILENO);
	//close(original_stdin);
	//dup2(original_stdout, STDOUT_FILENO);
	//close(original_stdout);
}

int	ft_number_child(t_ast *ast)
{
	int	i;

	i = 2;
	while (ast->right->type == N_PIPELINE)
		i++;
	return (i);
}

void	ft_pipeline(t_ast *ast, t_minishell *minishell, int pipe_in[2], int flag)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		pipefd_out[2];

	if (flag == 1)
	{
		dup2(pipe_in[0], STDIN_FILENO);
		close(pipe_in[1]);
	}
	if (pipe(pipefd_out) == -1)
			manage_error("pipe");
	pid_left = fork();
	if (!pid_left)
	{
		if (flag == 1)
		{
			ft_pipe_middle(ast->left, minishell, pipe_in, pipefd_out);
		}
		else
		{
			close(pipefd_out[0]);
			close(pipefd_out[1]);
			ft_pipe_child_left(ast->left, minishell, pipe_in);
		}
	}
	else
	{
		if (flag == 0)
		{
			dup2(pipe_in[0], pipefd_out[0]);
			//close(pipefd_out[0]);
			close(pipefd_out[1]);
		}
		close(pipe_in[0]);
		close(pipe_in[1]);
		if (ast->right->type == N_PIPELINE)
		{
			ft_pipeline(ast->right, minishell, pipefd_out, 1);
			close(pipefd_out[0]);
			close(pipefd_out[1]);
			//while (wait(NULL) > 0);
		}
		else
		{
			
			pid_right = fork();

			if (!pid_right)
			{
				//dup2(STDOUT_FILENO, minishell->stdout_fd);
				//close(minishell->stdout);
				ft_pipe_child_right(ast->right, minishell, pipefd_out);	
			}
			else
			{
				//close(pipe_in[0]);
				//close(pipe_in[1]);
				close(pipefd_out[0]);
				close(pipefd_out[1]);
				while (wait(NULL) > 0);
				//waitpid(pid_left, NULL, 0);
				//waitpid(pid_right, NULL, 0);
			}		
		}
	}
}

/*void	do_fork(t_ast *ast, int	pipefd_in[2], t_minishell *minishell)
{
    pid_t	pid;
    int	num_child;
    int	i;
    int		pipefd_out[2];
    int		status;

    num_child = ft_number_child(ast);
    i = 1;
    while (i <= num_child)
    {
        if (i != num_child)  // Don't create a new pipe for the last command
        {
            if (pipe(pipefd_out) == -1)
                manage_error("pipe");
        }
        pid = fork();
        if (!pid)
        {
            if (i == 1) // the first command
            {
                ft_pipe_child_left(ast->left, minishell, pipefd_in);
            }
            if (i < num_child && i > 1)  // Not the last command
            {
				ft_pipe_middle(ast->left, minishell, pipefd_in, pipefd_out);
            }
            if (i == 1)  // the last command
            {
				ft_pipe_child_right(ast->right, minishell, pipefd_out);	
            }
        }
		if (ast->right->type == N_PIPELINE)
		{
			ast = ast->right;
		}
        i++;
    }
    while (wait(&status) > 0);  // Wait for all child processes
}*/

/*void	ft_pipeline(t_ast *ast, t_minishell *minishell, int pipe_in[2], int flag)
{
	flag = 0;
	do_fork(ast, pipe_in, minishell);
	//wait(NULL);
}*/