// src/parser/argument_parser.h

#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H


#pragma once
#include <string>
#include <vector>

class ArgumentParser {
public:
    static std::vector<std::string> parse(const std::string& input);

private:
    enum class QuoteState {
        NONE,
        SINGLE_QUOTE,
        DOUBLE_QUOTE
    };

    static bool isWhitespace(char c);
    static bool isQuote(char c);
    // static std::string processEscapes(const std::string& arg);
};

#endif