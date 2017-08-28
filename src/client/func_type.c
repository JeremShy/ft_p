#include <client.h>

void	func_type(t_data *data)
{
	char	*send;
	char	*arg;
	char	*str;
	t_answer	answer;

	str = (data->cmd).cmd_tab[1];
	if (ft_strequ(str, "IMAGE") || ft_strequ(str, "BINARY") || ft_strequ(str, "I") || ft_strequ(str, "B"))
		arg = ft_strdup("I");
	else if (ft_strequ(str, "ASCII") || ft_strequ(str, "A"))
		arg = ft_strdup("A");
	else
	{
		ft_printf("Usage: type {{I || IMAGE || B || BINARY} || {A || ASCII}}\n");
		data->error = 1;
		return ;
	}
	send = build_request(NAME_RFC_TYPE, arg);
	free(arg);
	write(data->socket, send, ft_strlen(send));
	free(send);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
	if (answer.code / 100 > 2)
		data->error = 1;
	return ;
}
