#include <client.h>

t_data	*singleton_data(t_data *data)
{
	static t_data	*ret = NULL;

	if (!ret)
		ret = data;
	return (ret);
}
