#### Require library:
libzmq (ZeroMQ core engine in C++ https://github.com/zeromq/libzmq)                            
cppzmq (Header-only C++ binding for libzmq https://github.com/zeromq/cppzmq)                                   

The ZeroMQ lightweight messaging kernel is a library which extends the standard socket interfaces with features traditionally provided by specialised messaging middleware products. ZeroMQ sockets provide an abstraction of asynchronous message queues, multiple messaging patterns, message filtering (subscriptions), seamless access to multiple transport protocols and more.                

cppzmq is a C++ binding for libzmq. It has the following design goals:                  
cppzmq maps the libzmq C API to C++ concepts.                           
cppzmq is a light-weight, header-only binding. You only need to include the header file zmq.hpp (and maybe zmq_addon.hpp) to use it                     
zmq.hpp is meant to contain direct mappings of the abstractions provided by the libzmq C API, while zmq_addon.hpp provides additional higher-level abstractions.    


#### Setup (Linux kali 6.0.0-kali3-amd64 #1 SMP PREEMPT_DYNAMIC Debian 6.0.7-1kali1 (2022-11-07) x86_64 GNU/Linux)
```
sudo apt install libzmq3-dev
cd /home/kali/Desktop
mkdir libzmq && cd libzmq
wget https://github.com/zeromq/libzmq/archive/refs/tags/v4.3.4.zip
unzip v4.3.4.zip
cd libzmq-4.3.4
mkdir build && cd build
cmake ..
sudo make -j4 install

cd /home/kali/Desktop
mkdir cppzmq && cd cppzmq
wget https://github.com/zeromq/cppzmq/archive/refs/tags/v4.7.1.zip
unzip v4.7.1.zip
cd cppzmq-4.7.1
mkdir build && cd build
cmake -DCPPZMQ_BUILD_TESTS=off ..
sudo make -j4 install
```


#### How to use
```
cd zmq
make all
./server
./client
make clean
```


