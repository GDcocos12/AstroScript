#include <iostream>
#include <map>
#include <string>
#include <random>
#include <fstream>
#include <sstream>

std::map<std::string, double> variables;
int currline = 0;

void shutd() {
    system("pause");
    exit(0);
}

void handle_dclr(std::string variable_name, std::string data_type, std::string value) {
    currline++;
    double val;
    if (data_type == "int") {
        try {
            val = std::stod(value);
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else if (data_type == "float") {
        try {
            val = std::stod(value);
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    variables[variable_name] = val;
}

void handle_opr(std::string result_variable, std::string arg1, std::string action, std::string arg2) {
    currline++;
    double val1, val2;
    if (variables.count(arg1)) {
        val1 = variables[arg1];
    }
    else {
        val1 = std::stod(arg1);
    }
    if (variables.count(arg2)) {
        val2 = variables[arg2];
    }
    else {
        val2 = std::stod(arg2);
    }
    double result;
    if (action == "+") {
        try {
            result = val1 + val2;
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else if (action == "-") {
        try {
            result = val1 - val2;
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else if (action == "*") {
        try {
            result = val1 * val2;
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else if (action == "/") {
        try {
            result = val1 / val2;
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else if (action == "**") {
        try {
            result = pow(val1, val2);
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else {
        std::cout << "ERROR at line " << currline << ": " << "Invalid action" << std::endl;
        shutd();
        return;
    }
    variables[result_variable.substr(1, result_variable.size() - 2)] = result;
}

void handle_print(std::string value) {
    currline++;
    if (value[0] == '"' && value[value.size() - 1] == '"') {
        std::cout << value.substr(1, value.size() - 2) << std::endl;
    }
    else if (variables.count(value)) {
        std::cout << variables[value] << std::endl;
    }
    else {
        std::cout << value << std::endl;
    }
}

void handle_rnd(std::string variable_name, std::string min_value, std::string max_value) {
    currline++;
    double min_val, max_val;
    if (variables.count(min_value)) {
        min_val = variables[min_value];
    }
    else {
        min_val = std::stoi(min_value);
    }
    if (variables.count(max_value)) {
        max_val = variables[max_value];
    }
    else {
        max_val = std::stoi(max_value);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min_val, max_val);
    double result = dis(gen);
    variables[variable_name.substr(1, variable_name.size() - 2)] = (int)result;
}

void handle_copy(std::string variable1, std::string variable2) {
    currline++;
    if (variables.count(variable2)) {
        try {
            double value = variables[variable2];
            variables[variable1] = value;
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else {
        std::cout << "ERROR at line " << currline << ": " << "Variable not found" << std::endl;
        shutd();
    }
}

void handle_if(std::vector<std::string> tokens) {
    currline++;
    double arg1, arg2;
    if (variables.count(tokens[1])) {
        try {
            arg1 = variables[tokens[1]];
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else {
        try {
            arg1 = std::stod(tokens[1]);
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    if (variables.count(tokens[3])) {
        try {
            arg2 = variables[tokens[3]];
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    else {
        try {
            arg2 = std::stod(tokens[3]);
        }
        catch (const std::invalid_argument& ia) {
            std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
            shutd();
        }
    }
    bool condition;
    if (tokens[2] == ">") {
        condition = arg1 > arg2;
    }
    else if (tokens[2] == "<") {
        condition = arg1 < arg2;
    }
    else if (tokens[2] == ">=") {
        condition = arg1 >= arg2;
    }
    else if (tokens[2] == "<=") {
        condition = arg1 <= arg2;
    }
    else if (tokens[2] == "==") {
        condition = arg1 == arg2;
    }
    else if (tokens[2] == "!=") {
        condition = arg1 != arg2;
    }
    else {
        std::cout << "ERROR at line " << currline << ": " << "Invalid condition" << std::endl;
        shutd();
        return;
    }
    if (condition) {
        int i = 4;
        while (i < tokens.size()) {
            if (tokens[i] == "END") {
                break;
            }
            else if (tokens[i] == "DCLR") {
                handle_dclr(tokens[i + 1], tokens[i + 2], tokens[i + 3]);
            }
            else if (tokens[i] == "OPR") {
                handle_opr(tokens[i + 1], tokens[i + 2], tokens[i + 3], tokens[i + 4]);
            }
            else if (tokens[i] == "PRINT") {
                handle_print(tokens[i + 1]);
            }
            else if (tokens[i] == "RND") {
                handle_rnd(tokens[i + 1], tokens[i + 2], tokens[i + 3]);
            }
            else if (tokens[i] == "COPY") {
                handle_copy(tokens[i + 1], tokens[i + 2]);
            }
            else if (tokens[i] == "IF") {
                std::vector<std::string> nested_tokens;
                int nested_depth = 0;
                for (int j = i; j < tokens.size(); j++) {
                    if (tokens[j] == "IF") {
                        nested_depth++;
                    }
                    else if (tokens[j] == "END") {
                        nested_depth--;
                        if (nested_depth == 0) {
                            nested_tokens.push_back(tokens[j]);
                            break;
                        }
                    }
                    nested_tokens.push_back(tokens[j]);
                }
                handle_if(nested_tokens);
                i += nested_tokens.size();
            }
            i++;
        }
    }
}

void handle_ord(std::vector<std::string> tokens) {
    currline++;
    try {
        std::string variable_name = tokens[1].substr(1, tokens[1].size() - 2);
        char c = tokens[2][1];
        int ascii_code = static_cast<int>(c);
        variables[variable_name] = ascii_code;
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
        shutd();
    }
}

void handle_pow(std::string result_variable, std::string arg1, std::string arg2) {
    currline++;
    try {
        double val1, val2;
        if (variables.count(arg1)) {
            val1 = variables[arg1];
        }
        else {
            val1 = std::stod(arg1);
        }
        if (variables.count(arg2)) {
            val2 = variables[arg2];
        }
        else {
            val2 = std::stod(arg2);
        }
        double result = pow(val1, val2);
        variables[result_variable.substr(1, result_variable.size() - 2)] = result;
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
        shutd();
    }
}

void handle_inp(std::string result_variable) {
    currline++;
    try {
        std::string user_input;
        std::cout << "Enter value: ";
        std::cin >> user_input;
        variables[result_variable.substr(1, result_variable.size() - 2)] = std::stod(user_input);
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
        shutd();
    }
}

void execute_file(std::string filename) {
    currline++;
    try {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string command;
            bool in_string = false;
            while (std::getline(file, command, ';')) {
                std::vector<std::string> tokens;
                std::istringstream iss(command);
                std::string token;
                while (iss >> token) {
                    if (in_string) {
                        tokens.back() += " " + token.substr(0, token.size() - 1);
                        if (token.back() == '"') {
                            in_string = false;
                        }
                    }
                    else if (token.front() == '"') {
                        tokens.push_back(token.substr(1));
                        if (token.back() != '"') {
                            in_string = true;
                        }
                    }
                    else {
                        tokens.push_back(token);
                    }
                }
                if (tokens[0] == "DCLR") {
                    handle_dclr(tokens[1], tokens[2], tokens[3]);
                }
                else if (tokens[0] == "OPR") {
                    handle_opr(tokens[1], tokens[2], tokens[3], tokens[4]);
                }
                else if (tokens[0] == "PRINT") {
                    handle_print(tokens[1]);
                }
                else if (tokens[0] == "RND") {
                    handle_rnd(tokens[1], tokens[2], tokens[3]);
                }
                else if (tokens[0] == "IF") {
                    handle_if(tokens);
                }
                else if (tokens[0] == "COPY") {
                    handle_copy(tokens[1], tokens[2]);
                }
                else if (tokens[0] == "ORD") {
                    handle_ord(tokens);
                }
                else if (tokens[0] == "POW") {
                    handle_pow(tokens[1], tokens[2], tokens[3]);
                }
                else if (tokens[0] == "INP") {
                    handle_inp(tokens[1]);
                }
                else if (tokens[0] == "EXEC") {
                    if (tokens[1][0] == '{' && tokens[1].back() == '}') {
                        std::string filename = tokens[1].substr(1, tokens[1].length() - 2);
                        execute_file(filename);
                    }
                    else {
                        std::cout << "ERROR at line " << currline << ": " << "Invalid file name format" << std::endl;
                        shutd();
                    }
                }
                else if (tokens[0] == "END") {
                    break;
                }
            }
            file.close();
        }
        else {
            std::cout << "ERROR at line " << currline << ": " << "Unable to open file" << std::endl;
            shutd();
        }
    }
    catch (const std::invalid_argument& ia) {
        std::cout << "ERROR at line " << currline << ": " << ia.what() << std::endl;
        shutd();
    }
}

int main() {
    std::cout << "Welcome to ASTROSCRIPT INTERPRETER v1.2" << std::endl;
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string command;
        bool in_string = false;
        while (std::getline(file, command, ';')) {
            std::vector<std::string> tokens;
            std::istringstream iss(command);
            std::string token;
            while (iss >> token) {
                if (in_string) {
                    tokens.back() += " " + token.substr(0, token.size() - 1);
                    if (token.back() == '"') {
                        in_string = false;
                    }
                }
                else if (token.front() == '"') {
                    tokens.push_back(token.substr(1));
                    if (token.back() != '"') {
                        in_string = true;
                    }
                }
                else {
                    tokens.push_back(token);
                }
            }
            if (tokens[0] == "DCLR") {
                handle_dclr(tokens[1], tokens[2], tokens[3]);
            }
            else if (tokens[0] == "OPR") {
                handle_opr(tokens[1], tokens[2], tokens[3], tokens[4]);
            }
            else if (tokens[0] == "PRINT") {
                handle_print(tokens[1]);
            }
            else if (tokens[0] == "RND") {
                handle_rnd(tokens[1], tokens[2], tokens[3]);
            }
            else if (tokens[0] == "IF") {
                handle_if(tokens);
            }
            else if (tokens[0] == "COPY") {
                handle_copy(tokens[1], tokens[2]);
            }
            else if (tokens[0] == "ORD") {
                handle_ord(tokens);
            }
            else if (tokens[0] == "POW") {
                handle_pow(tokens[1], tokens[2], tokens[3]);
            }
            else if (tokens[0] == "INP") {
                handle_inp(tokens[1]);
            }
            else if (tokens[0] == "EXEC") {
                if (tokens[1][0] == '{' && tokens[1].back() == '}') {
                    std::string filename = tokens[1].substr(1, tokens[1].length() - 2);
                    execute_file(filename);
                }
                else {
                    std::cout << "ERROR at line " << currline << ": " << "Invalid file name format" << std::endl;
                    shutd();
                }
            }
            else if (tokens[0] == "END") {
                break;
            }
        }
        file.close();
    }
    else {
        std::cout << "ERROR at line " << currline << ": " << "Unable to open file" << std::endl;
        shutd();
    }

    system("pause");
    return 0;
}

