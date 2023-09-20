#include <iostream>
#include <string>
#include <algorithm>
#include <optional>
#include <array>
#include <math.h>

namespace
{
    using namespace std;
    using NumbersArray = int[3];

    optional<int> StringToInt(std::string numberString)
    {
        try
        {
            int number = std::stoi(numberString);


            return number;
        }
        catch (std::invalid_argument const& ex)
        {
            cout << "Not a number" << endl;
        }
        catch (std::out_of_range const& ex)
        {
            cout << "Number out of range" << endl;
        }

        return nullopt;
    }

    void LeftTrim(string& s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !isspace(ch);
            }));
    }

    bool ParseNumbers(string& input, NumbersArray numbers)
    {
        input = input + ' ';
        LeftTrim(input);
        size_t separator = input.find(' ');
        if (separator == string::npos)
        {
            return false;
        }

        for (int i = 0; i < 3; i++)
        {
            auto number = StringToInt(input.substr(0, separator + 1));
            if (number == nullopt)
            {
                return false;
            }
            numbers[i] = *number;
            input = input.substr(separator);
            LeftTrim(input);
            size_t separatorPos = input.find(' ');
            if (separatorPos == string::npos)
            {
                return false;
            }
        }
    }

    void ReadNumber(NumbersArray numbers)
    {
        string input;
        do
        {
            getline(cin, input);
        } while (input.empty());
        ParseNumbers(input, numbers);
    }

    optional<array<double, 2>> ResolveEquation(NumbersArray numbers)
    {
        double d = numbers[1] * numbers[1] - 4 * numbers[0] * numbers[2];
        if (d < 0 || numbers[0] == 0)
        {
            return nullopt;
        }
        array<double, 2> answers = { 0, 0 };
        answers[0] = (-numbers[1] - sqrt(d)) / (2 * numbers[0]);
        answers[1] = (-numbers[1] + sqrt(d)) / (2 * numbers[0]);

        return answers;
    }
}

int main()
{
    NumbersArray numbers = { 0, 0, 0 };
    cout << "Enter 3 numbers: " << endl;
    ReadNumber(numbers);
    auto answers = ResolveEquation(numbers);
    if (answers == nullopt)
    {
        cout << "No answers" << endl;
    }
    else
    {
        double firstAnswer = answers->at(0);
        double secondAnswer = answers->at(1);
        cout << firstAnswer << " " << secondAnswer << endl;
    }

    return EXIT_SUCCESS;
}