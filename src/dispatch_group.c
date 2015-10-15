#include <dispatch/dispatch.h>
#include <stdio.h>

int main(int argc, const char *argv[]) {
	dispatch_queue_t queue =
			dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0);

	dispatch_group_t group = dispatch_group_create();

	__block int sum = 0;

	for (int i = 0; i < 10; i++) {
		dispatch_group_async(group, queue, ^{
			printf("+%d\n", i);
			sum += i;
		});
	}

	dispatch_group_notify(group, queue, ^{
		printf("finish\n");
		dispatch_release(group);
		//<strike>dispatch_release(group);</strike>
	});

	dispatch_group_wait(group, DISPATCH_TIME_FOREVER);

	printf("sum = %d\n", sum);
	/* dispatch_release(group); */

	return 0;
}
