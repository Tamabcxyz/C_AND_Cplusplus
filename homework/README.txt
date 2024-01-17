install boost
cd /home/kali/
mkdir boost_1_84_0
cd $_
wget https://boostorg.jfrog.io/artifactory/main/release/1.84.0/source/boost_1_84_0.tar.bz2
tar --bzip2 -xf boost_1_84_0.tar.bz2
cd boost_1_84_0
./bootstrap.sh --prefix=/usr/local
./b2 install

sudo apt-get install libboost-serialization-dev
g++ -std=c++11 -o boost_binary boost_serialization.cpp -lboost_serialization