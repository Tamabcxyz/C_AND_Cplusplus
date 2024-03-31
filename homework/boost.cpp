// ==============create uuid using boost
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

int main() {
    auto uuid = boost::uuids::to_string(boost::uuids::random_generator()());
    std::cout << "Random UUID: " << uuid << std::endl;
    return 0;
}

// =============Variant type in boost
#include <iostream>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>

// Define some types to be used in the variant
struct Integer {
    int value;
    Integer() : value(0) {}
    Integer(int v) : value(v) {}
};

struct Double {
    double value;
    Double() : value(0.0) {}
    Double(double v) : value(v) {}
};

int main() {
    // Define a variant that can hold either an Integer or a Double
    boost::variant<Integer, Double> v;

    // Assign an Integer to the variant
    v = Integer(42);

    // Access and print the value
    if (v.which() == 0) {
        Integer i = boost::get<Integer>(v);
        std::cout << "Integer value: " << i.value << std::endl;
    } else {
        std::cout << "Not an Integer" << std::endl;
    }

    // Assign a Double to the variant
    v = Double(3.14);

    // Access and print the value
    if (v.which() == 1) {
        Double d = boost::get<Double>(v);
        std::cout << "Double value: " << d.value << std::endl;
    } else {
        std::cout << "Not a Double" << std::endl;
    }

    return 0;
}

// =============visitor and apply_visitor
#include <iostream>
#include <boost/variant.hpp>

// Define some types to be used in the variant
struct Integer { int value; };
struct Double { double value; };

// Define a static_visitor to perform operations on the variant types
struct MyVisitor : public boost::static_visitor<void> {
    //overload operation() to access the value stored inside boost::variant
    void operator()(const Integer& i) const {
        std::cout << "Integer value: " << i.value << std::endl;
    }

    void operator()(const Double& d) const {
        std::cout << "Double value: " << d.value << std::endl;
    }
};

int main() {
    // Define a variant that can hold either an Integer or a Double
    boost::variant<Integer, Double> v;

    // Assign an Integer to the variant
    v = Integer{42};

    // Apply the visitor to the variant
    boost::apply_visitor(MyVisitor{}, v);

    // Assign a Double to the variant
    v = Double{3.14};

    // Apply the visitor again
    boost::apply_visitor(MyVisitor(), v);

    return 0;
}

// =============lexical_cast in boost
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>

int main() {
    // Convert integer to string
    int num = 123;
    std::string numStr = boost::lexical_cast<std::string>(num);
    std::cout << "Integer to string: " << numStr << std::endl;

    // Convert string to integer
    std::string str = "456";
    int strNum = boost::lexical_cast<int>(str);
    std::cout << "String to integer: " << strNum << std::endl;

    return 0;
}

// =============split a string in boost
#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

int main() {
    std::string str = "apple,banana,orange";
    std::vector<std::string> tokens;

    // Split the string by comma delimiter
    boost::split(tokens, str, boost::is_any_of(","));

    // Print the tokens
    for (const auto& token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}

// =============removing leading and trailing whitespace characters from a string
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

int main() {
    std::string str = "   Hello, World!    ";
    
    // Trim leading and trailing whitespace
    boost::algorithm::trim(str);
    
    // Output the trimmed string
    std::cout << "Trimmed string: " << str << std::endl;
    
    return 0;
}

// =============replacing all occurrences of a substring within a string with another substring
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

int main() {
    std::string str = "apple banana apple banana apple";
    
    // Replace all occurrences of "apple" with "orange"
    boost::replace_all(str, "apple", "orange");
    
    // Output the modified string
    std::cout << "Modified string: " << str << std::endl;
    
    return 0;
}

// =============to_upper and to_lower
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>

int main() {
    std::string str = "Hello, World!";
    
    // Convert the string to uppercase
    boost::to_upper(str);
    std::cout << "Uppercase string: " << str << std::endl;
    
    // Convert the string to lowercase
    boost::to_lower(str);
    std::cout << "Lowercase string: " << str << std::endl;
    
    return 0;
}

// =============format a string like printf in c
#include <iostream>
#include <boost/format.hpp>

int main() {
    std::string name = "Alice";
    int age = 30;
    
    // Construct a formatted string with placeholders
    boost::format fmt("Hello, my name is %s and I am %d years old.");
    
    // Fill in the placeholders with actual values
    fmt % name % age;
    
    // Print the formatted string
    std::cout << fmt << std::endl;
    
    return 0;
}

// =============boost::thread_group
#include <iostream>
#include <boost/thread.hpp>

void threadFunction(int id) {
    std::cout << "Thread " << id << " is running." << std::endl;
}

int main() {
    // Create a thread group
    boost::thread_group threadGroup;

    // Add threads to the group
    for (int i = 0; i < 5; ++i) {
        threadGroup.create_thread(boost::bind(threadFunction, i));
    }

    // Wait for all threads to finish
    threadGroup.join_all();

    std::cout << "All threads have finished." << std::endl;

    return 0;
}

// =============boost::asio::post
#include <iostream>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <functional>
#include <vector>

void printMessage(const std::string& message) {
    std::cout << "Message: " << message << std::endl;
}

int main() {
    // Create a thread pool with 4 threads
    boost::asio::thread_pool threadPool(4);

    // Define messages to print
    std::vector<std::string> messages = {
        "Task 1 executed asynchronously",
        "Task 2 executed asynchronously",
        "Task 3 executed asynchronously",
        "Task 4 executed asynchronously"
    };

    // Submit each message as a task to the thread pool
    for (const auto& message : messages) {
        auto boundFunction = std::bind(printMessage, message);
        boost::asio::post(threadPool, boundFunction);
    }

    // Wait for all tasks in the thread pool to complete
    threadPool.join();

    return 0;
}




