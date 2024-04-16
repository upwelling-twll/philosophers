#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;


void	*printArr(int *str)
{
	//pthread_detach(t1);
	for (int i = 0; i < 15; i++)
		printf(" %i", str[i]);
	printf("\n");
	return (NULL);
}

void *print(void *arr)
{
	pthread_mutex_lock(&mutex);

	for (int i = 0; i < 15; i++)
		((int *)arr)[i] = i + ((int *)arr)[i];
	printArr((int *)arr);

	for (int i = 0; i < 15; i++)
		((int *)arr)[i] = ((int *)arr)[i] - i;
	printArr((int *)arr);	

	pthread_mutex_unlock(&mutex);

	printf("end\n");
	return (NULL);
}

// void *print2(void *arr)
// {
// 	for (int i = 0; i < 15; i++)
// 		((int *)arr)[i] = i + ((int *)arr)[i];
// 	printArr((int *)arr);

// 	for (int i = 0; i < 15; i++)
// 		((int *)arr)[i] = ((int *)arr)[i] - i;
// 	printArr((int *)arr);	
// 	printf("end\n");
// 	return (NULL);
// }

int	main(int argc, char *argv[])
{
	int	str1[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15} ;
	// char	*str2;

	// str1 = "11111111111111111111\n";
	// str2 = "22222222222222222222\n";
	// print(str1);
	// print(str2);
	pthread_t t1, t2;
		pthread_mutex_init(&mutex, NULL);
		pthread_create(&t1, NULL, print, (void *)str1);
		//pthread_detach(t1);
		
		pthread_create(&t2, NULL, print, (void *)str1);

		//pthread_detach(t2);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		usleep (1000000);

	write(1, "EXIT\n", 5);
}