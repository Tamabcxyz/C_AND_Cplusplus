#include <stdio.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    printf("Hello World\n");
    printf("Number of arguments: %d\n", argc);
    for(uint8_t i=0; i < argc; i++){
        printf("argv[%d]= %s\n", i, argv[i]);
    }
    return 0;
}

#include <stdio.h>
int main()
{
    printf("input from user: ");
    char input[100];
    //get input from user
    fgets(input, sizeof(input), stdin);
    //out
    printf("your entered: %s", input);
    return 0;
}

#include <stdio.h>
int main()
{
    int integer = 42;
    float floating_point = 3.14f;
    char character = 'A';
    char str[]="hello";
    unsigned int unsigned_int = 100;
    int hex_value = 255;
    // Printing an integer
    printf("Integer: %d\n", integer);
    // Printing a floating-point number
    printf("Floating-point: %f\n", floating_point);
    // Printing a character
    printf("Character: %c\n", character);
    // Printing a string
    printf("String: %s\n", str);
    // Printing an unsigned integer
    printf("Unsigned integer: %u\n", unsigned_int);
    // Printing in hexadecimal format
    printf("Hexadecimal (lowercase): %x\n", hex_value);
    printf("Hexadecimal (uppercase): %X\n", hex_value);
    // Printing a pointer address. If you don't cast to void*, some compilers might still accept it, but this behavior is not guaranteed by the C standard and may lead to warnings or undefined behavior.
    printf("Pointer address: %p\n", (void*)&integer);
    return 0;
}

// revert string C
#include <stdio.h>
#include <string.h>
void reverseString(char* str) {
    int length = strlen(str);
    int start = 0;
    int end = length - 1;
    char temp;
    while(start<end){
        temp = str[start];
        str[start]=str[end];
        str[end]=temp;
        start++;
        end--;
    }
}
int main()
{
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    reverseString(str);
    printf("Reversed string: %s\n", str);
    return 0;
}
//revert using pointer and one temp char type
#include <stdio.h>
#include <string.h>
void reverseString(char* str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    char temp;
    while(start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    reverseString(str);
    printf("Reversed string: %s\n", str);
    return 0;
}

//swap twos number without third variable
#include <stdio.h>

int main() {
    int a = 5; //0101
    int b = 10; //1010

    printf("Before swap: a = %d, b = %d\n", a, b);

    a = a ^ b;  // a now contains the XOR of a and b ==> a = 0101 XOR 1010 = 1111 = 15
    b = a ^ b;  // b now contains the original value of a ==> b = 1111 XOR 1010 = 0101 = 5
    a = a ^ b;  // a now contains the original value of b ==> a = 1111 XOR 0101 = 1010 = 10

    printf("After swap: a = %d, b = %d\n", a, b);

    return 0;
}

//find logest word in a string
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORD_LENGTH 100
void findLongestWord(char *str, char *longestWord) {
    int maxLen = 0;
    int currentLen = 0;
    char currentWord[MAX_WORD_LENGTH];
    while (*str) {
        // Skip leading spaces
        while (*str && isspace(*str)) {
            str++;
        }
        // Read a word
        currentLen = 0;
        while (*str && !isspace(*str)) {
            currentWord[currentLen++] = *str;
            str++;
        }
        currentWord[currentLen] = '\0';
        // Check if the current word is the longest
        if (currentLen > maxLen) {
            maxLen = currentLen;
            strcpy(longestWord, currentWord);
        }
    }
}
int main() {
    char str[] = "The quick brown fox jumps over the lazy dog";
    char longestWord[MAX_WORD_LENGTH];
    findLongestWord(str, longestWord);
    printf("The longest word is: %s\n", longestWord);
    return 0;
}
