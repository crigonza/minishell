/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:32:58 by crigonza          #+#    #+#             */
/*   Updated: 2023/03/23 12:56:58 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>


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
	char				**envp;
}						t_lexer;

typedef struct s_full_comm
{
	char				**command;
	int					pipe_next;
	int					semic_next;
	struct s_full_comm	*next;
}						t_full_comm;

typedef struct s_command
{
	struct s_full_comm	*command;
	char				**envp;
	int					filein;
	int					fileout;
	int					fd[2];
	int 				first_comm;
}						t_command;

//main.c
int						main(int argc, char **argv, char **envp);
void					init_prompt(t_list **envp, char **ev);
void					exit_v(char *prompt);
//lexer.c
void					free_lexer(t_lexer **lexer);
void					init_lexer(char *prompt, t_list **envp, char **ev);
int						get_string(t_lexer **lexer, char *prompt);
int						get_command(t_lexer **lexer, char *prompt);
int						get_num(t_lexer **lexer, char *prompt);
void					tokenize_prompt(t_lexer **lexer, char prompt);
t_lexer					*new_token(char *content, int token_type);
void					add_token(t_lexer **lexer, t_lexer *new);
t_lexer					*last_token(t_lexer *lexer);
//expander.c
void					full_path(t_lexer **lexer);
void					retokenize(t_lexer **lexer, t_list **envp);
void					expander(t_lexer **lexer, t_list **envp);
char					*get_envp_key(char *content);
char					*get_envp_value(t_list **envp, char *search);
char					*get_envp(char *content, t_list **envp);
//parser.c
t_full_comm				*last_command(t_full_comm *command);
void					parser(t_lexer **lexer, t_list **envp);
void					parse_command(t_full_comm **command, t_lexer **lexer);
void					add_command(t_full_comm **command, t_full_comm *new_command);
void					free_command(t_full_comm **command);
t_full_comm				*new_command(char **command, int pipe, int semic);
char					*set_command(char *command);
//executer.c
void					executer(char **command, char **envp);
void					execute_pipe(t_command *command);
void					execute(t_command *comm);
//builtin.c
void					is_builtin(t_full_comm *command, char **envp);
void					echo(char **command);
void					pwd(char **command);
void					cd(char **command);
void					env(t_list **envp, char **env);
void					export(char **envp, char **command);
//envp.c
void					list_envp(char **envp, t_list **envp_lst);
void					insert_env(t_list **envp, char **command);
//utils.c
void					print_lexer(t_lexer **lexer);
void					print_command(t_full_comm **command);

#endif