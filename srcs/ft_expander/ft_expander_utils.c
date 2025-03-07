#include "ft_expander.h"

int	ft_count_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}

t_token	*ft_token_maker_special(char **commands, t_token_type type)
{
	t_token	*token;
	t_token	*start;
	int		i;

	i = -1;
	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	start = token;
	while (commands[++i])
	{
		token->content = ft_strdup(commands[i]);
		token->type = type;
		token->heredoc = NULL;
		if (ft_strchr(commands[i], '"') || ft_strchr(commands[i], '\''))
			token->quotes = 1;
		token->quotes = 0;
		if (!commands[i + 1])
			break ;
		token->next = ft_calloc(sizeof(t_token), 1);
		token = token->next;
	}
	token->next = NULL;
	ft_free_matrix(commands);
	return (start);
}

int	ft_check_expander(t_token *tokens, size_t *i)
{
	if (tokens && tokens->content && ft_strlen(tokens->content) < (*i))
		return (0);
	while (tokens->content[*i] != '\0')
	{
		if (tokens->content[*i] == '$'
			&& tokens->content[*i + 1])
			return (1);
		if (tokens->content[*i] == '"')
		{
			(*i)++;
			while (tokens->content[(*i)] != '\0'
				&& tokens->content[(*i)] != '"')
			{
				if (tokens->content[(*i)] == '$')
					return (1);
				(*i)++;
			}
		}
		ft_check_expander2(tokens, i);
		if (tokens->content[(*i)])
			(*i)++;
	}
	return (0);
}
