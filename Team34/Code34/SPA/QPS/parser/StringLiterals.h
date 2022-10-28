#pragma once

#include <string>

namespace StringLiterals {
    const std::string FOLLOWS = "Follows";
    const std::string FOLLOWST = "Follows*";
    const std::string PARENT = "Parent";
    const std::string PARENTT = "Parent*";
    const std::string USES = "Uses";
    const std::string MODIFIES = "Modifies";
    const std::string NEXT = "Next";
    const std::string NEXTT = "Next*";
    const std::string CALLS = "Calls";
    const std::string CALLST = "Calls*";
    const std::string AFFECTS = "Affects";
    const std::string AFFECTST = "Affects*";

    // delimiters
    const std::string LEFT_BRACE = "(";
    const std::string RIGHT_BRACE = ")";
    const std::string SEMICOLON = ";";
    const std::string LEFT_ANGLE = "<";
    const std::string RIGHT_ANGLE = ">";
    const std::string UNDERSCORE = "_";
    const std::string HASHTAG = "#";
    const std::string QUATATION = "\"";
    const std::string COMMA = ",";
    const std::string FULLSTOP = ".";

    // operators
    const std::string MULTIPLE = "*";
    const std::string PLUS = "+";
    const std::string MINUS = "-";
    const std::string DIVIDE = "/";
    const std::string MODULO = "%";
    const std::string EQUAL = "=";

    // keywords
    const std::string SELECT = "Select";
    const std::string SUCH = "such";
    const std::string THAT = "that";
    const std::string BOOLEAN = "BOOLEAN";
    const std::string PATTERN = "pattern";
    const std::string WITH = "with";
    const std::string AND = "and";

    // attributes
    const std::string PROC_NAME = "procName";
    const std::string VAR_NAME = "varName";
    const std::string VALUE = "value";
    const std::string STMT = "stmt";
    const std::string STMT_NUM = STMT + HASHTAG;

}// namespace StringLiterals