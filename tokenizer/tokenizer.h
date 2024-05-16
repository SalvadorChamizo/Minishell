/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saroca-f <saroca-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:32:39 by saroca-f          #+#    #+#             */
/*   Updated: 2024/05/15 18:35:25 by saroca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>
# include <ctype.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include "./libft/include/libft.h" 

# define RED		"\x1b[31m"
# define GREEN   	"\x1b[32m"
# define YELLOW  	"\x1b[33m"
# define BLUE    	"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN    	"\x1b[36m"
# define WHITE		"\033[37m"
# define GREYM		"\x1B[38;5;245m"
# define GREYM2		"\x1B[38;5;250m"
# define BOLD		"\033[1m"
# define RESET   	"\x1b[0m"
# define CLEAR		"\033[2J"

typedef enum e_tokentype
{
	T_IDENTIFIER, //w
	T_COMMAND,
	T_BUILTIN,
	T_FILE,
	T_DELIMITER,
	T_LESS,	//r
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE, //pipe
	T_O_PARENT, //OP
	T_C_PARENT, //CP
	T_SQUOTE, //w
	T_DQUOTE,
	T_ASS, //=
	T_EOF,
}	t_tokentype;

typedef struct s_token
{
	t_tokentype			type;
	char				*value;
}	t_token;

typedef struct s_input
{
	t_token	*current_token;
	char	*line;
	char	**path;
	int		pos;
}	t_input;

typedef struct s_syntax
{
	t_token			*token;
	struct s_syntax	*left;
	struct s_syntax	*right;
}	t_syntax;

//tokenizer
t_token		*get_next_token(t_input *minishell);
void		ft_skip_spaces(t_input *input, char *text);
void		ft_sop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		ft_dop_def(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		s_quote_case(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
void		d_quote_case(t_input *mshll, t_token *nt, char *rt, t_tokentype t);
t_token		*tokenizer(t_input minishell);
bool		isoperator(char c);