#include <dispatch/dispatch.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[]) {
	dispatch_queue_t queue = dispatch_queue_create("timerQueue", 0);

	// Create dispatch timer source
	dispatch_source_t timer =
			dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 0, 0, queue);
	__block int i = 0;

	// Set block for dispatch source when catched events
	dispatch_source_set_event_handler(timer, ^{
		printf("%d\n", i);
		i++;
		if (i == 10) dispatch_source_cancel(timer);
	});

	// Set block for dispatch source when canceled source
	dispatch_source_set_cancel_handler(timer, ^{
		dispatch_release(timer);
		dispatch_release(queue);
		printf("end\n");
		exit(0);
	});

	dispatch_time_t start =
			dispatch_time(DISPATCH_TIME_NOW, NSEC_PER_SEC); // after 1 sec
	uint64_t interval = NSEC_PER_SEC / 5;								// 0.2 sec

	// Set timer
	dispatch_source_set_timer(timer, start, interval, 0);
	printf("start\n");

	dispatch_resume(timer);
	dispatch_main();
	return 0;
}
