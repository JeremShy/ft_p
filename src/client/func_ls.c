#include <client.h>

void	func_ls(t_data *data)
{
	int	data_socket;
	char	*send;
	t_answer	answer;

	data_socket = set_passive_mode(data);
	if (data->error)
	{
		ft_printf("Error while trying to open a passive connection\n");
		return;
	}
	send = build_request(NAME_RFC_LS, (data->cmd).cmd_tab[1]);
	write(data->socket, send, ft_strlen(send));
	free(send);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
	if (answer.code / 100 > 2)
	{
		data->error = 1;
		return ;
	}
	redirect_data(data_socket, 1);
	close(data_socket);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
}
