/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afogonca <afogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:39:29 by afogonca          #+#    #+#             */
/*   Updated: 2024/12/17 20:40:20 by afogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_free_token(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp)
	{
		token = temp -> next;
		free(temp->content);
		free(temp);
		temp = token;
	}
}

int		ft_cmdlen(char *str)
{
	int		i;
	int		j;
	char	type;

	j =0;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	i = j;
	if (str[i] == '"' || str[i] == '\'')
	{
		type = str[j++];
		i = j;
		while (str[i] != '\0' && str[i] != type)
			i++;
	}
	else
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		i++;
	return (i - j);
}

char	*ft_trim_cmd(char *str)
{
	char	*temp;
	char	type;
	int		i;
	int		j;

	temp = ft_calloc(ft_cmdlen(str) + 1, sizeof(char));
	printf("cmdlen: %i\n", ft_cmdlen(str));
	if (!temp)
		return (NULL);
	j = 0;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	i = 0;
	if (str[i] == '"' || str[i] == '\'')
	{
		type = str[j++];
		while (str[j] != '\0' && str[j] != type)
			temp[i++] = str[j++];
	}
	else
		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
			temp[i++] = str[j++];
	temp[i] = '\0';
	free(str);
	return (temp);
}

t_token	*ft_token_new(char *content, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_token_last(t_token *token)
{
	t_token	*temp;

	temp = token;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

t_token *ft_token_add_back(t_token *token, char *content, t_token_type type)
{
	t_token	*temp;

	temp = ft_token_new(content, type);
	if (!temp)
		return (NULL);
	if (!token)
		token = temp;
	else
	{
		temp->prev = ft_token_last(token);
		temp->prev->next = temp;
	}
	return (token);
}

/*char	*ft_trim_flags(char *str)*/
/*{*/
/**/
/*}*/

size_t	ft_split_len(char *str)
{
	size_t	count;
	size_t	i;
	char	type;

	count = 0;
	i = -1;
	printf("str: a%sa\n", str);
	while (str[++i] != '\0' && str[i] != 0 && str[i] != '\n')
	{
		printf("char: %d\n", str[i]);
		printf("char: %d\n", str[i]);
		if((str[i] != ' ' || str[i] != '\t') && str[i] != '\0')
		{
			while(str[i] != '\0' && str[i] != ' ' && str[i] != '\t'
				&& str[i] != '"' && str[i] != '\'')
				i++;
			count++;
			printf("count 1: %lu\n", count);
		}
		else if (str[i] == '"' || str[i] == '\'')
		{
			type = str[i];
			while (str[++i] != '\0')
			{
				if (str[i] == type)
				{
					count++;
					break ;
				}
			}
			printf("count 2: %lu\n", count);
		}
	}
	printf("count 3: %lu\n", count);
	return (count);
}

char	*ft_split_cmds(char *str)
{
	size_t	i;
	char	*temp;
	/*char	**info;*/

	temp = ft_strtrim(str, " ");
	if(!temp)
		return (NULL);
	i = ft_split_len(temp);
	free(temp);
	return (NULL);
}

/*t_token	*ft_tokens(char *str)*/
/*{*/
/*	char	**temp;*/
/*	char	*cmd;*/
/*	t_token	*token_start;*/
/*	t_token	*token;*/
/**/
/*	if (!str)*/
/*		return (NULL);*/
/*	free(cmd);*/
/*	return (token_start);*/
/*}*/

int	ft_check_quotes(char *str)
{
	size_t	i;
	size_t	found;
	char	type;

	i = -1;
	found = 0;
	if (!str)
		return (0);
	while (str[++i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			type = str[i];
			found = 1;
			while (str[++i] != '\0')
			{
				if (str[i] == type)
				{
					found = 0;
					break ;
				}
			}
			if (found == 1)
				return (1);
		}
	}
	return (0);
}

int main(void)
{
	char	*command;
	/*t_token	*token;*/

	while (1)
	{
		command = readline("Minishell: ");
		if (ft_check_quotes(command))
			ft_printf("dd_historySyntax error. Unbalanced quotes!\n");
		else
		{
			printf("%s\n", command);
			ft_split_cmds(command);
			/*token = ft_tokens(command);*/
			/*if (!token)*/
			/*	return (0);*/
			if (ft_strncmp(command, "exit", 4) == 0)
				return (0);
			/*if (ft_strncmp(token->content, "exit", 4) == 0)*/
			/*{*/
			/*	ft_free_token(token);*/
			/*	free(command);*/
			/*	return (0);*/
			/*}*/
			/*ft_printf("main: .%s\n", token->content);*/
			/*add_history(token->content);*/
			free(command);
			/*ft_free_token(token);*/
		}
	}
}
