#include <dispatch/dispatch.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main(int argc, char *argv[]) {
	int i;
	dispatch_queue_t q =
			dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);

	struct timespec ts3 = {3, 0};
	struct timespec ts1 = {1, 0};
	struct timeval basetime, etime;

	printf("loop start\n");
	gettimeofday(&basetime, NULL);
	for (i = 0; i < 10; i++) {
		dispatch_async(q, ^{
			pthread_t p = pthread_self();
			struct timeval tp;
			nanosleep(&ts3, NULL);
			gettimeofday(&tp, NULL);

			{
				int j = i;
				pthread_t q = pthread_self();
				struct timeval tq;
				gettimeofday(&tq, NULL);

				printf(
						"hello count %d\n"
						"running thread %p time: %ld\n"
						"printing thread %p time: %ld\n"
						"\n",
						j, p, tp.tv_sec - basetime.tv_sec, q, tq.tv_sec - basetime.tv_sec);
			}
		});
		nanosleep(&ts1, NULL);
	}
	printf("loop end\n");

	printf("all of them are gone. \n");
}

