#include <iostream>
#include <zmq.hpp>
#include <string>

using namespace std;

int main() {
    zmq::context_t context(1);// Create a ZeroMQ context
    zmq::socket_t responder(context, ZMQ_REP);// Create a ZeroMQ socket of type REP
    responder.bind("tcp://127.0.0.1:5555");  // Bind the socket to a TCP endpoint port 5555
    while(true){
        zmq::message_t request; // Create a message to received the request from client
        responder.recv(&request); // Received request from client

        std::string receiveMess(static_cast<char *>(request.data()),request.size());
        std::cout << "Received: " << receiveMess << std::endl;

        zmq::message_t reply(3);
        memcpy(reply.data(), "Hi", 3); // Set the message reply
        responder.send(reply); // Send reply to client
    }

  return 0;
}