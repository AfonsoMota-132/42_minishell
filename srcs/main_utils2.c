#include "../incs/minishell.h"

void	ft_free_loop3(t_data *data)
{
	ft_free_tokens(data->tokens, 1);
	data->tokens_start = data->tokens_end;
	data->tokens = data->tokens_start;
}
