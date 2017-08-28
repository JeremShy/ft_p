#include <client.h>

void	error_connection(t_data *data)
{
	ft_printf("Error : It seems you have been disconnected.\n");
	close(data->socket);
	exit(EXIT_FAILURE);
}
