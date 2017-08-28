#include <server.h>

void	func_quit(t_data *data)
{
	ft_putstr_fd("221 Goodbye.\r\n", data->pi_socket);
	close(data->pi_socket);
	return ;
}
