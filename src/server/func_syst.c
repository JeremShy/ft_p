#include <server.h>

void	func_syst(t_data *data)
{
	if (!data->logged_in)
		return (setret(data, 530, ERROR_NOT_LOGGED, 1));
	data->return_code = 215;
	data->commentaire = SYSTEM_NAME_AN;
	return ;
}
