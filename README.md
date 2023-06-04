# SDMBank

#how to instell catch2
Assuming you have enough rights, you can just install it to the default location, like so:
$ git clone https://github.com/catchorg/Catch2.git
$ cd Catch2
$ cmake -Bbuild -H. -DBUILD_TESTING=OFF
$ cmake --build build/ --target install