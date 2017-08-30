#include <client.h>

static int	get_fd(t_data *data, char *file)
{
	int	fd;

	if (!file)
		return (1);
	if ((fd = open(file, O_WRONLY | O_CREAT, 0666)) == -1)
	{
		ft_printf("Error while trying to open file %s\n", file);
		data->error = 1;
		return (-1);
	}
	return (fd);
}

void	func_get(t_data *data)
{
	int	data_socket;
	char	*send;
	t_answer	answer;
	int	fd;

	if (!data->cmd.cmd_tab[1])
	{
		ft_printf("Usage: get remote [local]\n");
		data->error = 1;
		return ;
	}
	data_socket = set_passive_mode(data);
	if (data->error)
	{
		ft_printf("Error while trying to open a passive connection\n");
		return;
	}
	if ((fd = get_fd(data, (data->cmd).cmd_tab[2])) == -1)
	{
		data->error = 1;
		close(data->socket);
		return ;
	}
	send = build_request(NAME_RFC_GET, (data->cmd).cmd_tab[1]);
	write(data->socket, send, ft_strlen(send));
	free(send);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
	if (answer.code / 100 > 2)
	{
		data->error = 1;
		free_answer(answer);
		return ;
	}
	redirect_data(data_socket, fd);
	close(data_socket);
	free_answer(answer);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
	free_answer(answer);
}
