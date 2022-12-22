#include "process.h"

#include <ctime>
#include <cstdlib>

Command::Command(int operand_type, int operation_type)
{
	this->operand_type = operand_type;
	this->operation_type = operation_type;
}

int Command::get_operand_type() const
{
	return operand_type;
}

int Command::get_operation_type() const
{
	return operation_type;
}

std::queue<Command*> create_random_commands(double operand_p,
                                            double operator_p,
                                            unsigned commands_count)
{
	srand(time(NULL));

	operand_p = operand_p * 100;
	operator_p = operator_p * 100;

	int operand_type = 0;
	int operation_type = 0;
	double random_number = 0;

	std::queue<Command *> commands;

	for (int i = 0; i < commands_count*5; ++i) {

		random_number = rand() / 100;
		if (operand_p < random_number)
			operand_type = REG;
		else
			operand_type = RAM;

		random_number = rand() / 100;
		if (operator_p < random_number)
			operation_type = OPERATION_1;
		else
			operation_type = OPERATION_2;

		auto new_command = new Command(operand_type,
					       operation_type);
		commands.push(new_command);
	}

	return commands;
}
