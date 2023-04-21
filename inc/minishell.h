/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:32:58 by crigonza          #+#    #+#             */
/*   Updated: 2023/04/21 20:58:15 by crigonza         ###   ########.fr       */
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
		SEMICOLON,
		PIPE,
	} token_type;
	char				*content;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_full_comm
{
	char				**command;
	int					pipe_next;
	int					semic_next;
	char				*filein;
	char				*fileout;
	int					fdin;
	int					fdout;
	struct s_full_comm	*next;
}						t_full_comm;

typedef struct s_command
{
	struct s_full_comm	*command;
	struct s_ev			**env;
}						t_command;

typedef struct s_ev
{
	char *key;
	char *value;
	struct s_ev *next;
}		t_ev;

typedef struct s_heredoc
{
	char	*line;
	struct s_heredoc *next;
}		t_heredoc;

//main.c
int						main(int argc, char **argv, char **envp);
int						init_prompt(t_ev **env);
int						exit_v(char *prompt);
void					free_envp(t_ev **env);
//lexer.c
void					free_lexer(t_lexer **lexer);
void					init_lexer(char *prompt, t_ev **envp);
int						get_string(t_lexer **lexer, char *prompt);
int						get_command(t_lexer **lexer, char *prompt);
int						get_num(t_lexer **lexer, char *prompt);
void					tokenize_prompt(t_lexer **lexer, char prompt);
t_lexer					*new_token(char *content, int token_type);
void					add_token(t_lexer **lexer, t_lexer *new);
//expander.c
void					full_path(t_lexer **lexer, t_ev **env);
void					retokenize(t_lexer **lexer, t_ev **envp);
void					expander(t_lexer **lexer, t_ev **envp);
char					*get_envp(t_ev **env, char *content);
char					*expand_envp(char *content, char *key, char *value);
void					get_full_path(char **path, t_lexer *lex);
char					*get_path(t_ev **env);
//parser.c
t_full_comm				*last_command(t_full_comm *command);
void					parser(t_lexer **lexer, t_ev **envp);
void					parse_command(t_full_comm **command, t_lexer **lexer);
void					add_command(t_full_comm **command, t_full_comm *new_command);
void					free_command(t_full_comm **command);
t_full_comm				*new_command(char **command, int pipe, int semic);
char					*set_command(char *command);
//executer.c
void					first_child(char **cmd, char **envp, int *prpipe);
void					last_child(char **cmd, char **envp, int prpipe);
void					exe_init(t_command *cmd);
void					solo_cmd(t_full_comm *cmd, char **envp);
void					execute_semi(t_full_comm **cmd, t_ev **l_env, char **env);
t_full_comm				*execute_pipe(t_full_comm **cmd, t_ev **l_env, char **env);
//builtin_utils.c
int						is_builtin(char *cmd);
void					builtin_exe(t_full_comm *cmd, t_ev **envp);
void					builtin_pipe(t_full_comm *cmd, t_ev **envp, int *prpipe);
int						check_key(t_ev **env, char *key, char *value);
//cd.c
void					cd_builtin(t_ev **envp, char **command);
void					change_pwd(t_ev **envp, char *path);
void					cd_home(t_ev **envp);
//builtin.c
void					echo_builtin(char **command);
void					pwd_builtin(char **command);
void					env_builtin(t_ev **envp, char **env);
void					export_builtin(t_ev **envp, char **command);
void					unset_builtin(t_ev **envp, char **command);
//envp.c
void 					set_envp(char **envp, t_ev **env);
void    				free_env_array(char **env);
char					**convert_envp(t_ev **env);
int						ev_len(t_ev **env);
t_ev					*new_ev(char *key, char *value);
void					add_ev(t_ev **env, t_ev *new);
//utils.c
void					print_lexer(t_lexer **lexer);
void					print_command(t_full_comm **command);
void					freedonia(char **out);
//signal.c
void					process_signal(int signum);
void					config_signals(void);
//heredoc.c
void					add_line(t_heredoc **hrdc, t_heredoc *new_hrdc);
void					heredoc(char *limit);
t_heredoc				*new_doc(char *str);
void					free_hrdc(t_heredoc **hrdc);
void					print_heredoc(t_heredoc **hrdc);
//redir.c
void    				file_in(t_full_comm *cmd);
void					file_out(t_full_comm *cmd);
int						check_redir(t_full_comm *cmd);
void					redir_solo_cmd(t_full_comm *cmd);

#endif
