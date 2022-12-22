#ifndef __PROCESS_H__
#define __PROCESS_H__

#include <queue>
#include <string>

enum OPERAND_TYPE {
    REG,
    RAM
};

enum OPERATION_TYPE {
    OPERATION_1 = 1,
    OPERATION_2
};

class Command
{
public:
	Command(int operand_type, int operation_type);

        int get_operand_type() const;
        int get_operation_type() const;
private:
	int operand_type;
	int operation_type;
};

std::queue<Command*> create_random_commands(double operand_p,
					    double operator_p,
					    unsigned commands_count);

#endif //__PROCESS_H__
