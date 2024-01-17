/**
 * Boost provides serialization facilities that can be used to serialize and
 * deserialize data structures in a portable and efficient way.
 */
/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java,
PHP, Ruby, Perl, C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C,
Assembly, HTML, CSS, JS, SQLite, Prolog. Code, Compile, Run and Debug online
from anywhere in world.

*******************************************************************************/
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/map.hpp>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
class Message {
private:
  int id;
  std::string message;

public:
  Message() = default;
  Message(int id, std::string msg) : id{id}, message{msg} {}
  std::string getMsg() const { return message; }
  int getID() const { return id; }

  friend class boost::serialization::access;
  template <typename Archive>
  void serialize(Archive &ar,
                 __attribute__((unused)) const unsigned int version) {
    //   ar &boost::serialization::base_object<typename>(*this);
    ar &id;
    ar &message;
  }
};

BOOST_CLASS_EXPORT_KEY(Message)
// BOOST_CLASS_EXPORT_IMPLEMENT(Message)

int main() {
  Message encodeMsg(1, "This message from Michael");

  std::stringstream serializeMsg;
  boost::archive::binary_oarchive encodeArchive(serializeMsg);
  encodeArchive << encodeMsg;

  std::cout << "Serialized message: " << serializeMsg.str() << std::endl;

  Message decodeMsg;
  boost::archive::binary_iarchive decodeArchive(serializeMsg);
  decodeArchive >> decodeMsg;

  std::cout << "Deserialized message: id: " << decodeMsg.getID()
            << " message: " << decodeMsg.getMsg() << std::endl;

  return 0;
}