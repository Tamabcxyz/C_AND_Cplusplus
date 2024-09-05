
#include <bitset>
#include <iostream>

int main() {
    unsigned int a = 5;   // Binary: 0101
    unsigned int b = 3;   // Binary: 0011
    std::cout << "a binary: " << std::bitset<4>(a) << std::endl;
    std::cout << "b binary: " << std::bitset<4>(b) << std::endl;

    std::cout << "a & b = " << std::bitset<4>(a & b) <<std::endl;   // Bitwise AND
    std::cout << "a | b = %" << std::bitset<4>(a | b)<<std::endl;   // Bitwise OR
    std::cout << "a ^ b = " << std::bitset<4>(a ^ b)<<std::endl;    // Bitwise XOR
    std::cout << "~a = " << std::bitset<4>(~a)<<std::endl;          // Bitwise NOT
    std::cout << "a << 1 = " << std::bitset<4>((a << 1))<<std::endl;// Left Shift
    std::cout << "a >> 1 = " << std::bitset<4>((a >> 1))<<std::endl;// Right Shift

    return 0;
}

// set bit test bit and clear bit
/**
 * & for test bit
 * | for set bit
 * & use to test and clear of bit (set the bit to zero) not use for set bit ==> bit nào muốn clear cho mark = 0, bit nào không clear mark = 1
 * ^ XOR toggle bit
 * I have state bool
 * state=0
 * state ^ 1 = 1; (state ^= 1;)
 * state = 1;
 * state ^ 1 = 0; (state ^= 1;)
 * ==>using XOR to change state
*/

#include <iostream>

/*
* set n th bit to 1
* N is number 
* n n th bit need to set to 1
*/
int setNbit(int N, int n) {
    int mask = 1 << (n-1);
    return (N|mask);
}

int main()
{
    int N = 5; // 0100
    int n = 4;
    
    //expected: 1100 = 13
    std::cout << setNbit(N, n);
    return 0;
}

//convert binary to decimal number
#include <iostream>
#include <string>
#include <cmath>
int binaryToDecimal(const std::string &binary) {
    int decimal = 0;
    int length = binary.length();
    // Iterate over each character in the binary string
    for (int i = 0; i < length; i++) {
        // Convert character to integer (0 or 1)
        std::cout << "binary: " << binary[length - 1 - i] << std::endl;
        int bit = binary[length - 1 - i] - '0';
        std::cout << "bit: " << bit << std::endl;
        // Calculate the value of the bit at position i
        decimal += bit * std::pow(2, i);
    }
    return decimal;
}
int main() {
    std::string binary = "1010";
    int decimal = binaryToDecimal(binary);
    std::cout << "Decimal equivalent: " << decimal << std::endl;
    return 0;
}

#include <iostream>
#include <string>
std::string decimalToBinary(int decimal) {
    if (decimal == 0) {
        return "0";
    }
    std::string binary = "";
    while (decimal > 0) {
        int remainder = decimal % 2;   // Get the remainder when divided by 2
        binary = std::to_string(remainder) + binary;  // Prepend the remainder to the binary string
        decimal = decimal / 2;  // Update decimal by dividing it by 2
    }
    return binary;
}
int main() {
    int decimal = 10;
    std::string binary = decimalToBinary(decimal);
    std::cout << "Binary equivalent: " << binary << std::endl;
    return 0;
}

//set bit, test bit, clear bit

#include <iostream>
#include <bitset>
bool testBit(int number, int n) {
    return (number & (1<<n -1)) != 0;
}
int setBit(int number, int n) {
    return number | (1<<n-1);
}
int clearBit(int number, int n) {
    return number & ~(1<<n-1);
}
int main() {
    int number = 0B1010; //10 in decimal
    //test bit: check if a bit at position 4th is set
    std::cout << testBit(number, 4) << std::endl; //1
    //set bit: set bit at potions 3th to 1
    std::cout << setBit(number, 3) << std::endl; //14
    //claer bit: clear a bit a position 3
    std::cout << clearBit(number, 3) << std::endl; //10
    return 0;
}

int main()
{
    int n = 0x00000001;
    //little endian: the least significant bit stored at the lowest memory addres
    //little endian: the most significant bit stored at the lowest memory addres
    // little endian: 0x01 0x00 0x00 0x00
    // big endian: 0x00 0x00 0x00 0x01
    unsigned char *c = (unsigned char *)&n;
    if(*c == 0x01) {
        std::cout << "little endian\n";
    } else if (*c == 0x00) {
        std::cout << "big endian\n";
    } else {
        std::cout << "unknow\n";
    }
    std::cout << static_cast<int>(*c);
    return 0;
}


//singleton
#include <iostream>
class Singleton{
  private:
  //do not allow to create object outside this class
  Singleton() = default;
  int data=3;
  public:
  Singleton(const Singleton&) = delete; //copy constructor = delete
  Singleton& operator=(const Singleton&) = delete; // copy assigment = delete
  Singleton& operator=(Singleton&&) = delete; // move assigment = delete
  static Singleton& getInstance(){
      static Singleton singleton;
      return singleton;
  }
  int getData(){
      return data;
  }
};
int main(){
    auto &a = Singleton::getInstance();
    std::cout << a.getData();
    return 0;
}

//100 prime numbers
#include <iostream>
#include <math.h>

bool checkPrime(int n) {
    if (n < 2) {
        return false;
    }
    for (int i=2; i<=sqrt(n); i++) {
        if(n%i==0){
            return false;
        }
    }
    return true;
}

int main()
{
    int count=0;
    int n = 2;
    while (count < 100) {
        if(checkPrime(n)){
            std::cout << n << " ";
            count++;
        }
        n++;
    }
    return 0;
}

//stack in c++
#include <iostream>
#include <stack>
int main()
{
    std::stack<int> s;
    s.push(1);s.push(5);s.push(3);s.push(7);
    std::cout << s.size() << std::endl;// 4
    std::cout << s.top() << std::endl; // 7
    s.pop();
    std::cout << s.top() << std::endl; // 3
    return 0;
}

//check a string is parentheses or not
#include <iostream>
#include <string>
#include <stack>
bool isValidParentheses(const std::string &str) {
    std::stack<char> s;
    for(const auto &c : str) {
        if (c=='[' || c=='(' || c=='{'){
            s.push(c);
        } else if(c==']' || c==')' || c=='}') {
            if(s.empty()) {
                return false;
            }
            if ((c==']' && s.top() != '[') || (c=='(' && s.top() != ')') || (c=='{' && s.top() != '}')) {
                return false;
            }
            s.pop();
        }
    }
    return true;
}
int main()
{
    // std::string str ="[({})]"; //valid
    std::string str ="[(({})]"; //invalid
    std::cout << isValidParentheses(str);
    return 0;
}

//queue
#include <iostream>
#include <queue>
int main()
{
    std::queue<int> q;
    q.push(1);q.push(5);q.push(3);q.push(7);
    std::cout << q.size() << std::endl;// 4
    std::cout << q.front() << std::endl;// 1
    std::cout << q.back() << std::endl;// 7
    q.pop();
    std::cout << q.front() << std::endl;// 5
    return 0;
}

//sort in c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
int main() {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    std::cout << "Sorted in descending order: ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}

// linked list c++
#include <iostream>

struct Node {
    int data;
    Node *next;
    Node(int value) : data(value), next(nullptr) {}
};

// Insert at head
Node* insertHead(Node *root, int value) {
    Node* newNode = new Node(value);
    newNode->next = root;
    return newNode; // Return the new head of the list
}

// Print the list
void printNode(Node *root) {
    while (root) {
        std::cout << root->data << " ";
        root = root->next;
    }
    std::cout << std::endl;
}

// Delete a node with a specific value
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) return nullptr; // List is empty

    // Handle deletion of the head node
    if (root->data == value) {
        Node* temp = root;
        root = root->next;
        delete temp;
        return root;
    }

    Node* current = root;
    while (current->next != nullptr && current->next->data != value) {
        current = current->next;
    }

    // Node to be deleted is found
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    return root;
}

// Clean up the list to prevent memory leaks
void deleteList(Node *root) {
    while (root) {
        Node *temp = root;
        root = root->next;
        delete temp;
    }
}

int main() {
    Node *root = new Node(10);
    root = insertHead(root, 5); // Insert 5 at head
    root = insertHead(root, 0); // Insert 0 at head
    std::cout << "List before deletion: ";
    printNode(root); // Print the list
    root = deleteNode(root, 5); // Delete node with value 5
    std::cout << "List after deletion: ";
    printNode(root); // Print the list
    return 0;
}

//revert number
#include <iostream>

int main() {
    int n = 12345678; //==>output: 87654321
    int result=0;
    while(n>0) {
        int temp = n%10;
        std::cout << temp << std::endl;
        n/=10;
        result = result*10+temp;
    }
    std::cout << "result: " << result;
    return 0;
}

//palindrome number
#include <stdio.h>
int main() {
  int n, reversed = 0, remainder, original;
    printf("Enter an integer: ");
    scanf("%d", &n);
    original = n;

    // reversed integer is stored in reversed variable
    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }

    // palindrome if orignal and reversed are equal
    if (original == reversed)
        printf("%d is a palindrome.", original);
    else
        printf("%d is not a palindrome.", original);

    return 0;
}

//armstrong number
#include <iostream>
#include <math.h>
int main() {
    int n = 371;
    int result=0;
    while(n>0) {
        int temp = n%10;
        std::cout << temp << std::endl;
        n/=10;
        result += pow(temp, 3);
    }
    std::cout << "result: " << result;
    return 0;
}

//C code reverse string recursive
#include <stdio.h>
void reverseSentence();
int main() {
    printf("Enter a sentence: ");
    reverseSentence();
    return 0;
}

void reverseSentence(){
    char c;
    scanf("%c", &c);
    if (c!='\n'){
        reverseSentence();
        printf("%c", c);
    }
}

//concat string without string strcat
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char s1[100]="hello";
    char s2[100]="kitty";
    //concat s2 to s1
    int lenS1;
    for(lenS1=0; s1[lenS1]!='\0'; ++lenS1);
    printf("%d", lenS1);
    int j;
    for(j=0; s2[j]!='\0'; j++) {
        s1[lenS1] = s2[j];
        lenS1++;
    }
    s1[lenS1]='\0';
    printf("\n concat string: %s", s1);
    printf("\n%d", strlen(s1));
    return 0;
}

//sort string
#include <stdio.h>
#include <string.h>

int main() {
   char str[5][50], temp[50];
   printf("Enter 5 words: ");
   // Getting strings input
   for (int i = 0; i < 5; ++i) {
      fgets(str[i], sizeof(str[i]), stdin);
   }
   // storing strings in the lexicographical order
   for (int i = 0; i < 5; ++i) {
      for (int j = i + 1; j < 5; ++j) {

         // swapping strings if they are not in the lexicographical order
         if (strcmp(str[i], str[j]) > 0) {
            strcpy(temp, str[i]);
            strcpy(str[i], str[j]);
            strcpy(str[j], temp);
         }
      }
   }
   printf("\nIn the lexicographical order: \n");
   for (int i = 0; i < 5; ++i) {
      fputs(str[i], stdout);
   }
   return 0;
}

