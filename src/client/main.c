#include <client.h>

static int	create_socket(int port, char *av, char *s_addr)
{
	struct protoent		*proto;
	int					ret;
	struct sockaddr_in	addr;

	proto = getprotobyname("tcp");
	if (!proto)
		return (pemr(av, "Error while trying to get the protocol\n"));
	if ((ret = socket(PF_INET, SOCK_STREAM, proto->p_proto)) == -1)
		return (pemr(av, "Error while trying to create a socket\n"));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(s_addr);
	if (connect(ret, (struct sockaddr*)(&addr), sizeof(struct sockaddr_in)) == -1)
		return (pemr(av, "Error while trying to connect the socket.\n"));
	return (ret);
}


void	print_prompt(t_data *data, int print_prompt)
{
	if (print_prompt)
	{
		if (data->error)
			ft_printf("Last command status: \e[38;5;1mERROR\e[39m\n");
		else
			ft_printf("Last command status: \e[38;5;2mSUCCESS\e[39m\n");
	}
	ft_putstr("\e[38;5;208m");
	ft_putstr(data->prompt);
	ft_putstr("\e[39m");
}

void	handle_line(t_data *data, char *cmd)
{
	if (!parse_cmd(data, cmd))
	{
		ft_printf("Command not found.\n");
		data->error = 1;
		return ;
	}
	data->tab[data->cmd.cmd_nbr](data);
}

void	init_tab(t_command_func *tab)
{
	tab[VALUE_LOGIN] = &func_login;
	tab[VALUE_PWD] = &func_pwd;
	tab[VALUE_CD] = &func_cd;
	tab[VALUE_TYPE] = &func_type;
	tab[VALUE_LS] = &func_ls;
	tab[VALUE_GET] = &func_get;
	tab[VALUE_PUT] = &func_put;
	tab[VALUE_QUIT] = &func_quit;
	tab[VALUE_SIZE] = &func_size;
}

void	reinit_data(t_data *data)
{
	data->error = 0;
}

int main(int ac, char **av)
{
	t_data data;
	char	*cmd;
	t_command_func tab[50];
	t_answer	answer;

	if (ac != 3)
	{
		ft_putstr_fd("usage: ", 2);
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" <machine> <port>\n", 2);
			return (1);
	}
	singleton_data(&data);
	signal(SIGINT, sigint);
	data.prompt = ft_strdup("ft_p$ ");
	data.machine = av[1];
	if ((data.port = ft_atoi(av[2])) <= 0)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(": invalid port\n", 2);
		return (2);
	}
	if (!(data.socket = create_socket(data.port, av[0], data.machine)))
		return (3);
	answer = get_answer(&data);
	if (answer.error <= 0)
		error_connection(&data);
	if (answer.error > 0)
		ft_printf("%s\n", answer.str);
	data.tab = tab;
	init_tab(data.tab);
	print_prompt(&data, 0);
	while(get_next_line(0, &cmd))
	{
		reinit_data(&data);
		handle_line(&data, cmd);
		print_prompt(&data, 1);
	}
	return (0);
}
