#include <client.h>

//TODO: Free answer dans les return

void	func_login(t_data *data)
{
	t_answer	answer;
	t_cmd	*cmd;
	char	*send;
	char	*username;
	char	*password;

	cmd = &(data->cmd);
	if (cmd->cmd_tab[1] == NULL)
	{
		ft_putstr("Usage: login username [password]\n");
		data->error = 1;
		return ;
	}
	username = cmd->cmd_tab[1];
	send = build_request(NAME_RFC_USER, username);
	password = NULL;
	if (cmd->cmd_tab[2])
		password = cmd->cmd_tab[2];
	write(data->socket, send, ft_strlen(send));
	free(send);
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	if (answer.code == 331 && !password)
	{
		ft_printf("%s\n", answer.str);
		data->error = 1;
		return ;
	}
	else if (answer.code == 230)
	{
		ft_putstr("Login successful.\n");
		return ;
	}
	else if (answer.code != 331)
	{
		ft_printf("%s\n", answer.str);
		data->error = 1;
		return ;
	}
	send = build_request(NAME_RFC_PASS, password);
	write(data->socket, send, ft_strlen(send));
	free(send);
	//TODO: free answer.
	answer = get_answer(data);
	if (answer.error <= 0)
		error_connection(data);
	if (answer.code == 530)
	{
		ft_printf("%s\n", answer.str);
		data->error = 1;
		return ;
	}
	else if (answer.code == 230)
	{
		ft_putstr("Login successful.\n");
		return ;
	}
	else
	{
		ft_printf("Error : %s\n", answer.commentaire);
		data->error = 1;
		return ;
	}
}
