#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream input("text.txt");
    std::ofstream output("text_copy.txt");
    std::string str;
    if (!input | !output) {
        std::cout << "Can't open file\n";
        return -1;
    }
    while(std::getline(input, str)){
        std::cout << str << std::endl;
        output << str;
    }
    
    input.close();
    output.close();
    return 0;
}

#include <iostream>
#include <string>
#include <unordered_map>

int countCharInString(const std::string &str, const char &c) {
    int count = 0;
    for(auto &a : str) {
        if(a == c) {
            count++;
        }
    }
    return count;
}

int main()
{
    // find number of character in string B appear in string A
    // A = "hello this is my string"
    // B = "thlk0"
    std::string str1 = "hello this is my string";
    std::string str2 = "thllk0";
    std::unordered_map<char, int> map{};
    for (char c : str2) {
        std::cout << c << std::endl;
        map[c] = countCharInString(str1, c);
    }
    std::cout << "=============" << std::endl;
    for (const auto &item : map) {
        std::cout << item.first << " " << item.second << std::endl;
    }
    return 0;
}

#include <iostream>
#include <string>
#include <map>

int countCharInString(const std::string &str, const char &c) {
    int count = 0;
    for(auto &a : str) {
        if(a == c) {
            count++;
        }
    }
    return count;
}

int main()
{
    // find number of character in string B appear in string A
    // A = "hello this is my string"
    // B = "thllk0"
    std::string str1 = "hello this is my string";
    std::string str2 = "thllk0";
    std::multimap<char, int> map{}; // help to store duplicate keys
    for (char c : str2) {
        std::cout << c << std::endl;
        map.insert({c,countCharInString(str1, c)});
    }
    std::cout << "=============" << std::endl;
    for (const auto &item : map) {
        std::cout << item.first << " " << item.second << std::endl;
    }
    return 0;
}


#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main() {
    // Input string
    std::string input = "This is a sample string";
    // Vector to store the separated words
    std::vector<std::string> words;
    std::stringstream ss(input);
    while(ss.good()){
        std::string substring;
        std::getline(ss, substring, ' ');
        words.push_back(substring);
    }
    for (const auto &item : words) {
        std::cout << item << std::endl;
    }
    return 0;
}




