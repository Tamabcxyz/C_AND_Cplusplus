/**
 * là một lớp template hỗ trợ trong c++17, nó thiết kế để đóng gói đối tượng có thể tồn tại hoặc không tồn tại (có thể có giá trị hoặc không)
 * nếu nó không chứa giá trị mà cố gắng truy cập thì sẽ trả về bad optional access
*/
#include <iostream>
#include <optional>
std::optional<int> plusEven(int a, int b) {
    if (a>0 && b>0) {
        return a+b; 
    } else {
        std::cout << "a or b is negative number\n";
        return std::nullopt;
    }
}

int main()
{
    int a = 5, b=-10;
    auto r = plusEven(a,b);
    std::cout << r.value();
    return 0;
}