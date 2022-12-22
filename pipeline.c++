#include "pipeline.h"

#include <iostream>
#include <numeric>

Pipeline::Pipeline(int access_ticks, int exe_time, std::queue<Command *> *commands)
: mem_access_ticks(access_ticks), exe_time(exe_time)
{
	for (int & i : count_ex_every_stage) {
		i = 0;
	}
	memory_blocked = false;
	tic_overall = 0;
	current_tact = 0;

	input_commands = commands;
	cmd_count = commands->size() / 5;

	for (auto & i : line)
		i = nullptr;
}

void Pipeline::work()
{
	while (pipeline_is_busy() || !input_commands->empty()) {
		current_tact++;
		is_memory_block();
		move_tact();
		fill_TPA();
		tact_info();
		clock();
	}
	exit();
}

int Pipeline::check_time_per_stage()
{
	return *std::max_element(tic_per_action.begin(), tic_per_action.end());
}

void Pipeline::fill_TPA()
{
	tic_per_action[0] = (line[0] != nullptr) ? 1 : 0;

	tic_per_action[1] = (line[1] != nullptr) ? 1 : 0;

	if (line[2] != nullptr)
		tic_per_action[2] = (line[2]->get_operand_type() == REG) ? 1 : mem_access_ticks;
	else tic_per_action[2] = 0;

	if (line[3] != nullptr)
		tic_per_action[3] = (line[3]->get_operation_type() == OPERATION_1) ? 1 : exe_time;
	else tic_per_action[3] = 0;

	if (line[4] != nullptr)
		tic_per_action[4] = (line[4]->get_operand_type() == REG) ? 1 : mem_access_ticks;
	else tic_per_action[4] = 0;

}

void Pipeline::is_memory_block()
{
	memory_blocked = line[0] != nullptr &&
			line[1] != nullptr &&
			line[2] != nullptr &&
			line[4] != nullptr;
}

void Pipeline::record_tact_time(Command *cmd)
{
	tic_per_cmd.push_back(check_time_per_stage());
}

bool Pipeline::pipeline_is_busy()
{
	return std::ranges::any_of(line.begin(), line.end(),
				   [](Command *i) { return i != nullptr; });
}

void Pipeline::move_tact()
{
	int stop = 0;
	stop = memory_blocked ? 1 : 0;

	int idx = line.size() - 1;
	if (line[idx] != nullptr) {
		record_tact_time(line[idx]);
		line[idx] = nullptr;
		count_ex_every_stage[idx] += tic_per_action[idx];
	}

	for (idx = line.size() - 2; idx >= stop; idx--) {
		if (line[idx] != nullptr && line[idx + 1] == nullptr) {
			line[idx + 1] = line[idx];
			line[idx] = nullptr;
			count_ex_every_stage[idx] += tic_per_action[idx];
		}
	}
	if (!memory_blocked && line[0] == nullptr && !input_commands->empty()) {
		line[0] = input_commands->front();
		input_commands->pop();
	}
}

void Pipeline::clock()
{
	tic_overall += check_time_per_stage();
}

void Pipeline::tact_info()
{
	std::cout << "Tact " << current_tact << std::endl;
	for (int i = 0; i < line.size(); i++) {
		std::cout << pipe_stages[i] << '\t';
		if (line[i] != nullptr) {
			std::cout << "Operation Type - " << line[i]->get_operation_type() << '\t' <<
			"Operand Type - " << line[i]->get_operand_type() << std::endl;
		}
		if(line[i] == nullptr){
			std::cout << "0" << std::endl;
		}
	}
	std::cout << '\n';
}

void Pipeline::exit()
{
	std::cout << "\n\n\n";
	std::cout << "Pipeline ended its work in " << tic_overall << " tics" << std::endl;

	double sum_time = std::accumulate(tic_per_cmd.begin(), tic_per_cmd.end(), 0);
	double average_cmd_time = sum_time / current_tact;
	std::cout << "Average time from 1 tact: " << average_cmd_time << " tics" << std::endl;

	sum_time = 0;
	for (int i : count_ex_every_stage)
		sum_time += i;

	for (int i = 0; i < COMMAND_SIZE; ++i) {
		std::cout << pipe_stages[i] << ": " <<
		((double)count_ex_every_stage[i] / (double)sum_time) * 100 << " %" << std::endl;
	}
}
