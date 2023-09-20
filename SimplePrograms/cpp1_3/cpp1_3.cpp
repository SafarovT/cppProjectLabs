#include <iostream>
#include <string>
#include <algorithm>
#include <optional>

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
        size_t secondSeparatorPos = input.find(' ');
        if (secondSeparatorPos == string::npos)
        {
            return false;
        }

        for (int i = 0; i < 3; i++)
        {
            auto number = StringToInt(input.substr(0, secondSeparatorPos));
            if (number == nullopt)
            {
                return false;
            }
            numbers[i] = *number;
            input = input.substr(secondSeparatorPos);
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
}

int main()
{
    NumbersArray numbersToSum = {0, 0, 0};
    cout << "Enter 3 numbers: " << endl;
    ReadNumber(numbersToSum);
    cout << "Sum = " << numbersToSum[0] + numbersToSum[1] + numbersToSum[2] << endl;

    return EXIT_SUCCESS;
}