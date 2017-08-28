#include <client.h>

void	redirect_data(int data_fd, int redir_fd)
{
	char	buff[BUFF_SIZE + 1];
	int		r;

	while ((r = read(data_fd, buff, BUFF_SIZE)))
		write(redir_fd, buff, r);
}
