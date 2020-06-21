#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cctype>

#include "calculator.h"

void remove_spaces(std::string &rez)
{
        for (int i = 0; i < rez.size(); ++i)
                if (std::isspace(rez[i])) {
                        rez.erase(rez.begin() + i, rez.begin() + i + 1);
                        --i;
                }
}

void prettify_string(std::string &str)
{
        std::string rez;

        remove_spaces(str);

        std::string operator_string = "+-/%*";

        for (char c : str)
                if (operator_string.find(c) != std::string::npos)
                        rez = rez + " " + c + " ";
                else
                        rez += c;
        str = rez;
}

int main(void)
{
        while (true) {
                std::string line;
                std::getline(std::cin, line);

                try {
                        Calculator c {line};

                        double value = c.evaluate_expression();

                        line.pop_back();

                        prettify_string(line);

                        std::cout << line << " = " << value << '\n';

                        std::ofstream ofs {".history", std::ios_base::app};
                        ofs << line << " = " << value << '\n';
                        ofs.close();
                } catch (std::exception& e) {
                }
        }

        return EXIT_SUCCESS;
}
