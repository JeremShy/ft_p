#include <client.h>

static char	*get_cwd_in_str(const char *str)
{
	int	i;
	int	len;

	i = 0;
	while (str[i] != '\"' && str[i])
		i++;
	if (!str[i])
		return (NULL);
	i++;
	len = 0;
	while (str[i + len] != '\"' && str[i + len])
		len++;
	return (ft_strsub(str, i, len));
}

void	func_pwd(t_data *data)
{
	char	*send;
	t_answer answer;

	send = build_request(NAME_RFC_PWD, "");
	write(data->socket, send, ft_strlen(send));
	free(send);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	if (answer.code == 257)
		ft_printf("Remote directory: %s\n", get_cwd_in_str(answer.commentaire));
	else if (answer.code == 530)
	{
		ft_printf("Unable to determine remote directory\n");
		data->error = 1;
		return ;
	}
	else
	{
		ft_printf("%s\n", answer.str);
		data->error = 1;
		return ;
	}
}
