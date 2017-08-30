#include <client.h>

void	pem(char *filename, char *message)
{
	if (filename)
	{
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message)
		ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

int		pemr(char *filename, char *message)
{
	pem(filename, message);
	return (0);
}

void	remove_cr(char *str)
{
	size_t	n;

	if (!str)
		return ;
	n = ft_strlen(str);
	if (n < 1)
		return ;
	if (str[n - 1] == 13)
	{
		str[n - 1] = '\0';
 		return ;
	}
}

void	set_error_and_ret(t_data *data, char *filename, char *message)
{
	data->error = 1;
	if (message)
		pem(filename, message);
	return ;
}

char	*build_request(const char *prefix, const char *suffix)
{
	char	*request;

	request = ft_strdup(prefix);
	request = ft_strjoinaf1(request, " ");
	if (suffix)
		request = ft_strjoinaf1(request, suffix);
	request = ft_strjoinaf1(request, "\r\n");
	return (request);
}

void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
