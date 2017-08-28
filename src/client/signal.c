#include <client.h>

void	sigint(int sig)
{
	t_data	*data;

	(void)sig;
	data = singleton_data(NULL);
	ft_printf("\n");
	print_prompt(data, 0);
}
