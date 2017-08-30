#include <client.h>

void	free_cmd(t_cmd cmd)
{
	if (cmd.cmd_tab)
		free_double_tab(cmd.cmd_tab);
}

int	get_value(char *str)
{
	if (ft_strequ(str, NAME_LOGIN))
		return (VALUE_LOGIN);
	else if (ft_strequ(str, NAME_PWD))
		return (VALUE_PWD);
	else if (ft_strequ(str, NAME_CD))
		return (VALUE_CD);
	else if (ft_strequ(str, NAME_TYPE))
		return (VALUE_TYPE);
	else if (ft_strequ(str, NAME_LS))
		return (VALUE_LS);
	else if (ft_strequ(str, NAME_GET))
		return (VALUE_GET);
	else if (ft_strequ(str, NAME_PUT))
		return (VALUE_PUT);
	else if (ft_strequ(str, NAME_QUIT))
		return (VALUE_QUIT);
	else if (ft_strequ(str, NAME_SIZE))
		return (VALUE_SIZE);
	return (-1);
}

int	parse_cmd(t_data *data, char *str)
{
	t_cmd	*cmd;

	cmd = &(data->cmd);
	data->cmd_str = ft_strdup(str);
	if ((cmd->cmd_tab = ft_special_split(str)) == NULL)
		return (0);
	if ((cmd->cmd_nbr = get_value(cmd->cmd_tab[0])) == -1)
		return (0); //TODO: free things ?
	return (1);
}
