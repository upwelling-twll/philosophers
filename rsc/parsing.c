#include "../phylosopher.h"

t_param	*parsing(int argc, char **argv)
{
	t_param 		*data;

	if (argc < 2 || !argv)
		return (NULL);
	data = malloc(sizeof(t_param));
	data->n = 3;
	data->time_to_eat = 100*1000; //one hundred thousand microseconds
	data->time_to_die = 200*1000;
	data->time_to_sleep = 100*1000;
	data->turns_to_eat = 0;
	return (data);
}
