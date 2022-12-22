#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include <array>
#include <vector>
#include <queue>
#include <string>

#include "process.h"

#define COMMAND_SIZE 5


class Pipeline
{
public:
	Pipeline(int access_ticks, int exe_time, std::queue<Command *> *commands);

	void work();

private:
	int check_time_per_stage();

	void fill_TPA();

	void move_tact();

	void clock();

	void is_memory_block();

	void record_tact_time(Command *cmd);

	bool pipeline_is_busy();

	void tact_info();

	void exit();

private:

	// Pipeline parameters
	const int mem_access_ticks;
	const int exe_time;

	// Pipeline states
	bool memory_blocked;

	// Pipeline input and internals
	std::queue<Command *> *input_commands;
	unsigned cmd_count;

	std::vector<int> tic_per_cmd;

	std::array<Command *, COMMAND_SIZE> line;
	std::array<int, COMMAND_SIZE> tic_per_action;
	int count_ex_every_stage[COMMAND_SIZE];

	int tic_overall;
	int current_tact;

	const char* pipe_stages[COMMAND_SIZE] = {"IF&ID",
					 "OR1",
		                         "OR2",
		                         "EX",
		                         "WB"};


};


#endif //__PIPELINE_H__
