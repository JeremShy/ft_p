#include <client.h>

void	func_quit(t_data *data)
{
	char	*send;
	t_answer	answer;

	send = build_request(NAME_RFC_QUIT, "");
	write(data->socket, send, ft_strlen(send));
	free(send);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
	close(data->socket);
	exit(0);
}
