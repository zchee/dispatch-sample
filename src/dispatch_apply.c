#include <dispatch/dispatch.h>
#include <stdio.h>

int main(int argc, const char* argv[]) {
	dispatch_queue_t queue = dispatch_get_global_queue(QOS_CLASS_DEFAULT, 0);

	__block int sum = 0;

	dispatch_apply(10, queue, ^(size_t i) {
		printf("i: %zd\n", i);
		sum += i;
		printf("sum: %d\n", sum);
	});
	sleep(1);

	printf("sum = %d\n", sum); // sumは45になる

	return 0;
}
