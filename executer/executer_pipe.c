/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schamizo <schamizo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:24:21 by schamizo          #+#    #+#             */
/*   Updated: 2024/06/13 12:59:26 by schamizo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bash.h"

/*void	ft_pipe_middle2(t_ast *ast, t_minishell *minishell, int pipe_mid[2])
{
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	close(minishell->pipe_out[1]);
	if (minishell->pipe_check == 1)
		dup2(minishell->pipe_aux[0], STDIN_FILENO);
	else
		dup2(minishell->pipe_out[0], STDIN_FILENO);
	close(minishell->pipe_in[0]);
	dup2(minishell->pipe_in[1], STDOUT_FILENO);
	close(minishell->pipe_out[0]);
	close(minishell->pipe_in[1]);
	minishell->middle_count++;
	ft_simple_command2(ast, minishell);
}*/

void	ft_pipe_middle(t_ast *ast, t_minishell *minishell)
{
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	dup2(ast->token->fd_0, STDIN_FILENO);
	close(ast->token->fd_0);
	close(ast->token->fd_aux0);
	dup2(ast->token->fd_1, STDOUT_FILENO);
	close(ast->token->fd_aux1);
	close(ast->token->fd_1);
	if (minishell->pipe_check == 1)
	{
		if (minishell->infile_check == 1)
		{
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->fd_in_redir, STDIN_FILENO);
			close(minishell->fd_in_redir);
		}
		if (minishell->outfile_check == 1)
		{
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			dup2(minishell->fd_out_redir, STDOUT_FILENO);
			close(minishell->fd_out_redir);
		}
	}
	minishell->middle_count++;
	//close(minishell->stdin_fd);
	//close(minishell->stdout_fd);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_left(t_ast *ast, t_minishell *minishell)
{
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		//minishell->pipe_aux[] = ast->token->fd_1;
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	close(ast->token->fd_0);
	dup2(ast->token->fd_1, STDOUT_FILENO);
	close(ast->token->fd_aux1);
	//close(ast->token->fd_aux0);
	close(ast->token->fd_1);
	if (minishell->pipe_check == 1)
	{
		if (minishell->infile_check == 1)
		{
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->fd_in_redir, STDIN_FILENO);
			close(minishell->fd_in_redir);
		}
		if (minishell->outfile_check == 1)
		{
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			dup2(minishell->fd_out_redir, STDOUT_FILENO);
			close(minishell->fd_out_redir);
		}
	}
	//close(minishell->stdin_fd);
	//close(minishell->stdout_fd);
	ft_simple_command2(ast, minishell);
}

void	ft_pipe_child_right(t_ast *ast, t_minishell *minishell)
{
	if (ast->type != N_COMMAND)
	{
		minishell->pipe_check = 1;
		ft_executer(ast, minishell);
		exit(0);
	}
	if (ast->right)
	{
		minishell->pipe_check = 1;
		ft_executer(ast->right, minishell);
	}
	close(ast->token->fd_1);
	dup2(ast->token->fd_0, STDIN_FILENO);
	close(ast->token->fd_0);
	close(ast->token->fd_aux1);
	close(ast->token->fd_aux0);
	if (minishell->pipe_check == 1)
	{
		if (minishell->infile_check == 1)
		{
			dup2(minishell->stdin_fd, STDIN_FILENO);
			dup2(minishell->fd_in_redir, STDIN_FILENO);
			close(minishell->fd_in_redir);
		}
		if (minishell->outfile_check == 1)
		{
			dup2(minishell->stdout_fd, STDOUT_FILENO);
			dup2(minishell->fd_out_redir, STDOUT_FILENO);
			close(minishell->fd_out_redir);
		}
	}
	//close(minishell->stdin_fd);
	//close(minishell->stdout_fd);
	ft_simple_command2(ast, minishell);
}

void	ft_pipeline(t_ast *ast, t_minishell *minishell, int flag)
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;
	t_ast	*temp;

	status = 0;
	printf("left pipefd: read: %d write: %d\n", ast->left->token->fd_0, ast->left->token->fd_1);
	printf("left pipefd: read_aux: %d write_aux: %d\n", ast->left->token->fd_aux0, ast->left->token->fd_aux1);
	if (ast->right->type != N_PIPELINE)
	{
		printf("right pipefd: read: %d write: %d\n", ast->right->token->fd_0, ast->right->token->fd_1);
		printf("right pipefd: read_aux: %d write_aux: %d\n", ast->right->token->fd_aux0, ast->right->token->fd_aux1);
	}
	pid_left = fork();
	if (!pid_left)
	{
		if (flag == 1)
		{
			temp = ast;
			while (temp->right->type == N_PIPELINE)
			{
				ft_putnbr_fd(temp->right->token->pipefd[0], 2);
				ft_putstr_fd(" pipefd[0]\n", 2);
				ft_putnbr_fd(temp->left->token->fd_0, 2);
				ft_putstr_fd(" fd_0\n", 2);
				if (temp->right->token->pipefd[0] != ast->left->token->fd_0)
					close(temp->right->token->pipefd[0]);
				ft_putnbr_fd(temp->right->token->pipefd[1], 2);
				ft_putstr_fd(" pipefd[1]\n", 2);
				ft_putnbr_fd(temp->left->token->fd_1, 2);
				ft_putstr_fd(" fd_1\n", 2);
				if (temp->right->token->pipefd[1] != ast->left->token->fd_1)
					close(temp->right->token->pipefd[1]);
				temp = temp->right;
			}
			ft_pipe_middle(ast->left, minishell);
		}
		else
		{
			temp = ast;
			while (temp->right->type == N_PIPELINE)
			{
				close(temp->right->token->pipefd[0]);
				close(temp->right->token->pipefd[1]);
				temp = temp->right;
			}
			ft_pipe_child_left(ast->left, minishell);
		}
	}
	else
	{
		if (ast->right->type == N_PIPELINE)
		{
			close(ast->token->pipefd[1]);
			ft_pipeline(ast->right, minishell, 1);
			close(ast->token->pipefd[0]);
			while (wait(&status) > 0)
				continue ;
		}
		else
		{
			close(ast->token->pipefd[1]);
			pid_right = fork();
			if (!pid_right)
				ft_pipe_child_right(ast->right, minishell);
			else
			{
				close(ast->token->pipefd[0]);
				close(ast->token->pipefd[1]);
				if (flag == 0)
					while (wait(&status) > 0)
						continue ;
			}
		}
	}
	minishell->status = WEXITSTATUS(status);
}
