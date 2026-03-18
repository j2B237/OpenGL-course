echo "Cleanup project....."
echo "\n"

rm *.o

echo "Compiling files..."

g++ -Wall -Werror -pedantic -c main.cxx
g++ -Wall -Werror -pedantic -c glad.c

echo "\n"
echo "Linking obj files ..."

g++ *.o -ldl -glfw -o application

echo "\n"
echo "Done ..."


