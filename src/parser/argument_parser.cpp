// src/parser/argument_parser.cpp
#include "argument_parser.h"
#include <stdexcept>

std::vector<std::string> ArgumentParser::parse(const std::string& input) {
    std::vector<std::string> tokens;
    std::string current;
    QuoteState quote_state = QuoteState::NONE;
    bool escape = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (escape) {
            if (quote_state == QuoteState::NONE) {
                // Outside quotes, handle special escape sequences
                switch (c) {
                    case 'n': current += '\n'; break;
                    case 't': current += '\t'; break;
                    case 'r': current += '\r'; break;
                    default: 
                        // For other characters, preserve the character
                        current += c;
                        break;
                }
            } else if (quote_state == QuoteState::DOUBLE_QUOTE) {
                // In double quotes, preserve the escape character
                current += '\\';
                current += c;
            } else {
                // In single quotes, treat as literal
                current += c;
            }
            escape = false;
            continue;
        }

        if (c == '\\') {
            // Mark for potential escaping
            escape = true;
            continue;
        }

        switch (quote_state) {
            case QuoteState::NONE:
                if (isWhitespace(c)) {
                    if (!current.empty()) {
                        tokens.push_back(current);
                        current.clear();
                    }
                } else if (c == '\'' || c == '"') {
                    quote_state = (c == '\'') ? QuoteState::SINGLE_QUOTE : QuoteState::DOUBLE_QUOTE;
                } else {
                    current += c;
                }
                break;

            case QuoteState::SINGLE_QUOTE:
                if (c == '\'') {
                    quote_state = QuoteState::NONE;
                } else {
                    current += c;
                }
                break;

            case QuoteState::DOUBLE_QUOTE:
                if (c == '"') {
                    quote_state = QuoteState::NONE;
                } else {
                    current += c;
                }
                break;
        }
    }

    // Handle last token and escape
    if (!current.empty()) {
        tokens.push_back(current);
    }

    if (quote_state != QuoteState::NONE) {
        throw std::runtime_error("Unbalanced quotes");
    }

    return tokens;
}

bool ArgumentParser::isWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

bool ArgumentParser::isQuote(char c) {
    return c == '\'' || c == '"';
}

// std::string ArgumentParser::processEscapes(const std::string& arg) {
//     std::string processed;
//     bool escape = false;
//     bool inDoubleQuotes = false;

//     for (size_t i = 0; i < arg.length(); ++i) {
//         char c = arg[i];

//         if (c == '"') {
//             inDoubleQuotes = !inDoubleQuotes;
//             processed += c;
//             continue;
//         }

//         if (escape) {
//             // In double quotes or followed by a space, preserve backslash
//             if (inDoubleQuotes || 
//                 (i < arg.length() - 1 && (arg[i] == ' ' || arg[i] == '\t'))) {
//                 processed += '\\';
//             }
//             processed += c;
//             escape = false;
//         } else if (c == '\\') {
//             if (inDoubleQuotes) {
//                 // Inside double quotes, preserve backslash
//                 processed += '\\';
//             } else {
//                 // Outside quotes, mark for potential escaping
//                 escape = true;
//             }
//         } else {
//             processed += c;
//         }
//     }

//     // Handle trailing backslash
//     if (escape && !inDoubleQuotes) {
//         processed += '\\';
//     }

//     return processed;
// }