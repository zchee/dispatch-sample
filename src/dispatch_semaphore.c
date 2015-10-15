#include <dispatch/dispatch.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, const char* argv[]) {
	dispatch_queue_t queue =
			dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
	dispatch_group_t group = dispatch_group_create();

	dispatch_semaphore_t semaphore = dispatch_semaphore_create(1);

	for (int i = 0; i < 10; i++) {
		dispatch_group_async(group, queue, ^{
			// Enable semaphore
			dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);

			// ==  Start critical session  ==
			printf("start %zd\n", i);
			usleep(10000);
			printf("end %zd\n", i);
			// ==  End critical session  ==

			// Send semaphore signal
			dispatch_semaphore_signal(semaphore);
		});
	}

	// Wait for loop...
	dispatch_group_wait(group, DISPATCH_TIME_FOREVER);

	dispatch_release(semaphore);
	dispatch_release(group);

	return 0;
}
