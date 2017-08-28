#include <server.h>

void	func_cwd(t_data *data)
{
	t_command	cmd;

	if (!data->logged_in)
		return (setret(data, 530, ERROR_NOT_LOGGED, 1));
	cmd = *(data->cmd);
	if (!cmd.argument || !can_be_oppenedir(cmd.argument, data->exec_path) || chdir(cmd.argument) == -1)
	{
		data->return_code = 550;
		data->commentaire = " Failed to change directory.";
		data->error = 1;
		return ;
	}
	data->return_code = 250;
	data->commentaire = " Directory successfully changed";
	return ;
}
