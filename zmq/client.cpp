#include <iostream>
#include <zmq.hpp>
#include <string>

using namespace std;

int main() {
    zmq::context_t context(1); // Create zmq context
    zmq::socket_t requestor(context, ZMQ_REQ); // Create a ZeroMQ socket of type REQ
    requestor.connect("tcp://127.0.0.1:5555"); // Connect the socket to the server

    std::string sendMess("Hello"); // initial message to send to server
    zmq::message_t requestMess(sendMess.size());
    memcpy(requestMess.data(), sendMess.c_str(), sendMess.size()); // Copy request to message_t
    requestor.send(requestMess); // Sent request to server

    zmq::message_t receivedMess;
    requestor.recv(&receivedMess); // Recieved reply from server
    std::string receivedMessStr(static_cast<char *> (receivedMess.data()), receivedMess.size());
    std::cout << "Received: " << receivedMessStr << std::endl;

  return 0;
}