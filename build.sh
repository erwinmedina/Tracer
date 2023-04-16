# Compile
g++ -c -Wall -m64 -std=c++17 -o main.o main.cpp

# Link
g++ -m64 -o final.out main.o -std=c++17

./final.out

rm *.o
rm *.out