// Centralized command handler implementation

#include "command_handler.h"
#include "../builtins/builtins.h"
#include "../utils/path_utils.h"
#include "../parser/argument_parser.h"

#include <iostream>
#include <sstream>
#include <queue>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_map>

using CommandFunc = std::string (*)(const std::string &);

std::unordered_map<std::string, CommandFunc> commandHandlers = {
    {"echo", handleEcho},
    {"exit", handleExit},
    {"type", handleType},
    {"pwd", handlePWD},
    {"cd", handleCD}};

void executeCommand(const std::string &input)
{

    try
    {
        std::vector<std::string> tokens = ArgumentParser::parse(input); // Parse the input into tokens , i.e. command and arguments
        if (tokens.empty())
            return;

        std::string cmd = tokens[0]; // First token is the command
        std::string args; // Space preserved arguments

        // Reconstruct arguments as a single string
        if (tokens.size() > 1)
        {
            // Join all tokens after the command with spaces
            for (size_t i = 1; i < tokens.size(); ++i)
            {
                args += tokens[i];
                if (i < tokens.size() - 1)
                {
                    args += " ";
                }
            }
        }
        // Handle built-in commands
        if (commandHandlers.find(cmd) != commandHandlers.end())
        {
            auto result = commandHandlers[cmd](args);
            if (!result.empty())
                std::cout << result << std::endl;
        }
        // Handle external commands
        else if (isExternalCommand(cmd))
        {
            std::string execPath = findExecutable(cmd); // Find the executable path to fork into

            if (execPath.empty())
            {
                std::cerr << cmd << ": command not found" << std::endl;
                return;
            }

            // Convert parsed token to char* array for execvp
            std::vector<char *> c_args;
            c_args.push_back(const_cast<char *>(cmd.c_str())); // First argument is the command itself
            for (size_t i = 1; i < tokens.size(); ++i)
            {
                c_args.push_back(const_cast<char *>(tokens[i].c_str()));
            }
            c_args.push_back(nullptr); // Last argument must be NULL

            // Fork and execute the command
            pid_t pid = fork();
            if (pid == 0)
            {
                // Child process
                execvp(execPath.c_str(), c_args.data()); // Syntax execvp (command in char*, args in char*[] array)
                perror("execvp");                        // Print error message if execvp fails
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                // Parent Process
                int status;
                waitpid(pid, &status, 0); // Wait for the child process to finish
                /* Syntax waitpid (process id, status, options)

                    process id = pid of the child process
                    pid == 0 means wait for any child process in the same process group
                    pid > 0 means wait for the child process with the given pid
                    pid == -1 means wait for any child process

                    options = 0 means wait for any child process
                    option = WNOHANG means don't wait ,
                    option = WUNTRACED means wait for stopped child process
                    option = WCONTINUED means wait for continued child process

                    status = 0 means success ,
                    status = 1 means failure ,
                    status = 2 means suspend,
                    status = 3 means resume ,
                    status = 4 means terminate ,
                    status = 5 means stop ,
                    status = 6 means continue ,
                    status = 7 means kill ,
                    status = 8 means exit ,
                    status = 9 means abort ,
                    status = 10 means signal ,

                */
            }
            else
            {
                perror("fork"); // Print error message if fork fails
            }
        }
        else
        {
            std::cout << cmd << ": command not found" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error parsing command: " << e.what() << std::endl;
    }
}
