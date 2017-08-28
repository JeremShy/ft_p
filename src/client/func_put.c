#include <client.h>

static int	get_fd(t_data *data, char *file)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_printf("Error while trying to open file %s\n", file);
		data->error = 1;
		return (-1);
	}
	return (fd);
}

void	func_put(t_data *data)
{
	int	data_socket;
	char	*send;
	t_answer	answer;
	int	fd;

	if (!data->cmd.cmd_tab[1] || !data->cmd.cmd_tab[2])
	{
 		ft_printf("Usage: put local remote\n");
		data->error = 1;
		return ;
	}
	data_socket = set_passive_mode(data);
	if (data->error)
	{
		ft_printf("Error while trying to open a passive connection\n");
		return;
	}
	if ((fd = get_fd(data, (data->cmd).cmd_tab[1])) == -1)
	{
		close(data_socket);
		ft_printf("%s\n", answer.str);
		return ;
	}
	send = build_request(NAME_RFC_PUT, (data->cmd).cmd_tab[2]);
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
	redirect_data(fd, data_socket);
	close(data_socket);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	ft_printf("%s\n", answer.str);
}
