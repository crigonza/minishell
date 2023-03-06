/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:32:58 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/06 21:20:36 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_lexer
{
	enum
	{
		STRING,
		COMMAND,
		PATH,
		SLASH,
		MINUS,
		GREATER_THAN,
		LESS_THAN,
		SEMICOLON,
		PIPE,
		L_PAR,
		R_PAR,
		DOLLAR
	} token_type;
	char				*content;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_command
{
	char				*command;
	char				**path;
	struct s_command	*next;
	int					in;
	int					out;
}						t_command;

//main.c
int						main(void);
void					init_prompt(void);
//lexer.c
void					free_lexer(t_lexer **lexer);
void					init_lexer(char *prompt);
int						get_string(t_lexer **lexer, char *prompt);
int						get_command(t_lexer **lexer, char *prompt);
int						get_num(t_lexer **lexer, char *prompt);
void					tokenize_prompt(t_lexer **lexer, char prompt);
t_lexer					*new_token(char *content, int token_type);
void					add_token(t_lexer **lexer, t_lexer *new);
t_lexer					*last_token(t_lexer *lexer);
//parser.c
t_command				*last_command(t_command *command);
void					parser(t_lexer **lexer);
void					add_command(t_command **command,
							t_command *new_command);
t_command				*new_command(char *command, char **path);
char					*set_command(char *command);
//utils.c
void					print_lexer(t_lexer **lexer);
void					print_command(t_command **command);

#endif