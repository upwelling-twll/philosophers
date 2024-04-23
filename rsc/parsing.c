#include "../phylosopher.h"

t_param	*parsing(int argc, char **argv)
{
	t_param *data;

	if (argc < 2 || !argv)
		return (NULL);
	data = malloc(sizeof(t_param));
	data->n = 4;
	data->time_to_eat = 100*1000;
	data->time_to_die = 100*1000;
	data->time_to_sleep = 100*1000;
	return (data);
}
