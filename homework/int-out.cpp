// std::cin reads input until it encounters whitespace (spaces, tabs, or newlines), so it would only capture the first word of the input.
// std::getline reads input as a whole line and stores it in the string, making it easier to handle complete lines of text.
#include <iostream>
#include <algorithm>
int main()
{
    std::cout<<"input: ";
    std::string input;
    std::cin >> input; //only get string to space
    std::reverse(input.begin(), input.end());
    std::cout << input;
    return 0;
}

#include <iostream>
#include <algorithm>
int main()
{
    std::cout<<"input: ";
    std::string input;
    std::getline(std::cin, input); //getline get entier string 
    std::reverse(input.begin(), input.end());
    std::cout << input;
    return 0;
}
