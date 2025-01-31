#include <iostream>
#include "core/command_handler.h"

int main()
{
    while (true)
    {
        std::cout << "\033[32m$ \033[0m" << std::flush;
        std::string input;
        std::getline(std::cin, input);

        if (std::cin.eof())
            break;
        if (input.empty())
            continue;

        executeCommand(input);
    }
    return 0;
}
