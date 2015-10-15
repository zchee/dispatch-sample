#include <dispatch/dispatch.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char* argv[])

{
	dispatch_queue_t gQueue = dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0);

	dispatch_async(gQueue, ^{

		dispatch_queue_t sQueue = dispatch_queue_create(
				"com.github.zchee.godispatch.example", DISPATCH_QUEUE_CONCURRENT);

		for (int i = 0; i < 10; i++) {
			dispatch_sync(sQueue, ^{
				printf("block %d\n", i);
			});
		}

		dispatch_release(sQueue);

		printf("finish\n");
		exit(0);
	});

	dispatch_main();

	return 0;
}
