#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	struct timeval	time;
	struct timeval	time2;
	struct timeval	zone;
	long long	start;

	gettimeofday(&time, &zone);
	start = time.tv_sec;
	printf("start=%lli\n", start);
	printf("start=%li\n", time.tv_usec);
	int i = 0;
	while (i < 200)
		i++;
	printf("\n%i\n", gettimeofday(&time2, &zone));
	printf("%li\n", time2.tv_sec);
	printf("%li\n", time2.tv_usec);
	printf("diff=%li\n", time2.tv_usec - time.tv_usec);
	return (0);
}