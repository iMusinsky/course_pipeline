#include "pipeline.h"

int main()
{
	auto cmd_queue1 = create_random_commands(0.9, 0.9, 1000);

	Pipeline pipe1(2, 4, &cmd_queue1);
	pipe1.work();

/*
	auto cmd_queue2 = create_random_commands(0.8, 0.7, 1000);

	Pipeline pipe2(5, 8, &cmd_queue2);
	pipe2.work();

	auto cmd_queue3 = create_random_commands(0.6, 0.5, 1000);

	Pipeline pipe3(10, 16, &cmd_queue3);
	pipe3.work();
 */
	return 0;
}
