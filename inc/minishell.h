/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 21:32:58 by crigonza          #+#    #+#             */
/*   Updated: 2023/05/10 23:45:46 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>

int						g_exit_value;

typedef struct s_lexer
{
	enum
	{
		STRING,
		COMMAND,
		PIPE,
		LESS_THAN,
		GREATER_THAN,
		D_LESS_THAN,
		D_GREATER_THAN,
	} token_type;
	char				*content;
	struct s_lexer		*next;
}						t_lexer;

typedef struct s_full_comm
{
	char				**command;
	int					pipe_next;
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
	char				*key;
	char				*value;
	struct s_ev			*next;
}						t_ev;

typedef struct s_heredoc
{
	char				*line;
	struct s_heredoc	*next;
}						t_heredoc;

//builtin_utils.c
int						is_builtin(char *cmd);
void					builtin_exe_pid(t_full_comm *cmd, t_ev **envp);
void	last_builtin_pipe(t_full_comm *cmd,
						t_ev **envp,
						int prpipe);
void	builtin_pipe(t_full_comm *cmd,
					t_ev **envp,
					int *prpipe);
int						check_key(t_ev **env, char *key, char *value);
//builtin.c
void					echo_builtin(char **command);
void					pwd_builtin(void);
void					env_builtin(t_ev **envp, char **command);
void					unset_builtin(t_ev **envp, char **command);
void					builtin_exe(t_full_comm *cmd, t_ev **envp);
//cd.c
void					change_pwd(t_ev **envp, char *path);
void					cd_home(t_ev **envp);
void					cd_builtin(t_ev **envp, char **command);
//echo.c
int						close_quotes(char *prompt);
int						check_echo_opt(t_lexer **lexer, char *prompt);
int						without_quotes(t_lexer **lexer, char *prompt);
char					*clean_quotes(char *prompt, int quotes, int len);
int						with_quotes(t_lexer **lexer, char *prompt, int quotes);
//envp.c
t_ev					*new_ev(char *key, char *value);
void					add_ev(t_ev **env, t_ev *new);
void					free_env_array(char **env);
char					**convert_envp(t_ev **env);
void					set_envp(char **envp, t_ev **env);
//executer_utils.c
void					solo_cmd(t_full_comm *cmd, char **envp);
//executer.c
void					first_child(t_full_comm *cmd, char **envp, int *prpipe);
void					last_child(t_full_comm *cmd, char **envp, int prpipe);
void					exe_init(t_command *cmd);
void					execute(t_full_comm **cmd, t_ev **l_env, char **env);
void	execute_pipe(t_full_comm **cmd,
					t_ev **l_env,
					char **env);
//expander_utils.c
void					syntax_error(char *cmd);
void					retokenize(t_lexer **lexer, t_ev **envp);
char					*get_path(t_ev **env);
void					get_full_path(char **path, t_lexer *lex);
void					full_path(t_lexer **lexer, t_ev **env);
//expander.c
char					*expand_envp(char *content, char *key, char *value);
char					*get_envp(t_ev **env, char *content);
int						check_squotes(char *str);
void					expand_ret_val(t_lexer **lexer);
void					expander(t_lexer **lexer, t_ev **envp);
//export_utils.c
void					export_builtin(t_ev **envp, char **command);
void					change_values(t_ev *current, t_ev *next);
//export.c
void					order_vars(t_ev **envp);
void					print_order_ev(t_ev **envp);
t_ev	*export_whout_args_aux(t_ev *tmp,
							t_ev *env,
							t_ev *ordered_env);
void					export_whout_args(t_ev **envp);
void					export(t_ev **env, char *key, char *value);
//heredoc.c
void					add_line(t_heredoc **hrdc, t_heredoc *new_hrdc);
t_heredoc				*new_doc(char *str);
void					free_hrdc(t_heredoc **hrdc);
void					print_heredoc(t_heredoc **hrdc);
void					heredoc(char *limit);
//lexer_utils.c
int						get_echo_string(t_lexer **lexer, char *prompt);
int						get_command(t_lexer **lexer, char *prompt);
int						set_tokens(char first, char next, t_lexer **lexer);
//lexer.c
void					free_lexer(t_lexer **lexer);
int						get_string(t_lexer **lexer, char *prompt);
void					add_token(t_lexer **lexer, t_lexer *new);
void					init_lexer(char *prompt, t_ev **envp);
t_lexer					*new_token(char *content, int token_type);
//main.c
int						main(int argc, char **argv, char **envp);
void					finish_init(char *prompt, t_ev **env);
int						init_prompt(t_ev **env);
int						exit_v(char *prompt);
void					free_envp(t_ev **env);
//parser.c
void					parser(t_lexer **lexer, t_ev **envp);
void					parse_command(t_full_comm **command, t_lexer **lexer);
void					free_command(t_full_comm **command);
void	add_command(t_full_comm **command,
					t_full_comm *new_command);
t_full_comm				*new_command(char **command, int pipe);
//redir.c
void					file_out(t_full_comm *cmd, int i);
void					file_in(t_full_comm *cmd, int i);
int						check_redir_aux(t_full_comm *cmd, int i);
int						check_redir(t_full_comm *cmd);
void					redir_solo_cmd(t_full_comm *cmd);
//signal.c
void					process_signal(int signum, siginfo_t *info,
							void *context);
void					config_signals(void);
//utils.c
void					print_lexer(t_lexer **lexer);
void					print_command(t_full_comm **command);
int						ft_strcmp(char *str1, char *str2);
int						ev_len(t_ev **env);
int						get_count(t_lexer **lexer);
void					free_tmp(t_ev *tmp);


#endif
