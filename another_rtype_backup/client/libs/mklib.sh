#!/bin/sh
echo "Building dynamic libs\nRemoving the old :)\n"

find ./ \( -name "*~" -delete -or -name "#*#" -delete -or -name "*.so" -delete \) -print

echo "\nCompiling the new libs"
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Player1.so ../src/Player1.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Player2.so ../src/Player2.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Player3.so ../src/Player3.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Player4.so ../src/Player4.cpp

g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Monster1.so ../src/Monster1.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Monster2.so ../src/Monster2.cpp


g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./weapons/Weapon1.so ../src/Weapon1.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./weapons/Weapon2.so ../src/Weapon2.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./weapons/Weapon3.so ../src/Weapon3.cpp
g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./weapons/Weapon4.so ../src/Weapon4.cpp

g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./ships/Boss1.so ../src/Boss1.cpp

g++ -Wall -Wextra -fPIC -shared -I../header -I/usr/local/boost_1_39_0/ -o ./decors/Explosion1.so ../src/Explosion1.cpp

echo "\ndone.."