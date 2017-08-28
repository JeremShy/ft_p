#include <server.h>

void	handle_sigchld(int p)
{
	p = 0;
	wait4(-1, NULL, WNOHANG, NULL);
}
