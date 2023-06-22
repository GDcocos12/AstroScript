#include <iostream>
#include <string>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

std::unordered_map<std::string, double> variables;

void handle_dclr(std::string variable_name, std::string data_type, std::string value) {
    if (data_type == "int") {
        variables[variable_name] = std::stoi(value);
    }
    else if (data_type == "float") {
        variables[variable_name] = std::stof(value);
    }
}

void handle_opr(std::string result_variable, std::string arg1, std::string action, std::string arg2) {
    double num1, num2;
    if (variables.find(arg1) != variables.end()) {
        num1 = variables[arg1];
    }
    else {
        num1 = std::stod(arg1);
    }
    if (variables.find(arg2) != variables.end()) {
        num2 = variables[arg2];
    }
    else {
        num2 = std::stod(arg2);
    }
    double result;
    if (action == "+") {
        result = num1 + num2;
    }
    else if (action == "-") {
        result = num1 - num2;
    }
    else if (action == "*") {
        result = num1 * num2;
    }
    else if (action == "/") {
        result = num1 / num2;
    }
    else if (action == "**") {
        result = pow(num1, num2);
    }
    else {
        std::cout << "Invalid action" << std::endl;
        return;
    }
    variables[result_variable.substr(1, result_variable.size() - 2)] = result;
}

void handle_print(std::string value) {
    if (value[0] == '"' && value[value.size() - 1] == '"') {
        std::cout << value.substr(1, value.size() - 2) << std::endl;
    }
    else if (variables.find(value) != variables.end()) {
        std::cout << variables[value] << std::endl;
    }
    else {
        std::cout << value << std::endl;
    }
}

void handle_rnd(std::string variable_name, std::string min_value, std::string max_value) {
    double min, max;
    if (variables.find(min_value) != variables.end()) {
        min = variables[min_value];
    }
    else {
        min = std::stod(min_value);
    }
    if (variables.find(max_value) != variables.end()) {
        max = variables[max_value];
    }
    else {
        max = std::stod(max_value);
    }
    srand(time(NULL));
    double result = min + (max - min) * rand() / RAND_MAX;
    variables[variable_name.substr(1, variable_name.size() - 2)] = result;
}

void handle_copy(std::string variable1, std::string variable2) {
    if (variables.find(variable2) != variables.end()) {
        double value = variables[variable2];
        variables[variable1] = value;
    }
    else {
        std::cout << "Variable not found" << std::endl;
    }
}

void handle_if(std::vector<std::string> tokens) {
    double arg1, arg2;
    if (variables.find(tokens[1]) != variables.end()) {
        arg1 = variables[tokens[1]];
    }
    else {
        arg1 = std::stod(tokens[1]);
    }
    if (variables.find(tokens[3]) != variables.end()) {
        arg2 = variables[tokens[3]];
    }
    else {
        arg2 = std::stod(tokens[3]);
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
        std::cout << "Invalid condition" << std::endl;
        return;
    }
    if (condition) {
        for (int i = 4; i < tokens.size(); i++) {
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
        }
    }
}

void handle_ord(std::vector<std::string> tokens) {
    std::string variable_name = tokens[1].substr(1, tokens[1].size() - 2);
    char ch = tokens[2][1];
    int ascii_code = static_cast<int>(ch);
    variables[variable_name] = ascii_code;
}

void handle_pow(std::string result_variable, std::string arg1, std::string arg2) {
    double num1, num2;
    if (variables.find(arg1) != variables.end()) {
        num1 = variables[arg1];
    }
    else {
        num1 = std::stod(arg1);
    }
    if (variables.find(arg2) != variables.end()) {
        num2 = variables[arg2];
    }
    else {
        num2 = std::stod(arg2);
    }
    double result = pow(num1, num2);
    variables[result_variable.substr(1, result_variable.size() - 2)] = result;
}

void handle_inp(std::string result_variable) {
    std::string user_input;
    std::cout << "Enter value: ";
    std::cin >> user_input;
    variables[result_variable.substr(1, result_variable.size() - 2)] = std::stod(user_input);
}

int main() {
    std::cout << "Welcome to DUDOLIN INTERPRETER v1.0" << std::endl;
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string command;
        while (std::getline(file, command, ';')) {
            std::vector<std::string> tokens;
            std::istringstream iss(command);
            std::string token;
            while (iss >> token) {
                tokens.push_back(token);
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
            else if (tokens[0] == "END") {
                break;
            }
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file" << std::endl;
    }

    system("pause");
    return 0;
}
