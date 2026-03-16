echo "Cleanup...."

rm *.o

echo "Compiling files..."

g++ -Wall -Werror -pedantic -c main.cxx
g++ -Wall -Werror -pedantic -c glad.c
g++ -Wall -Werror -pedantic -c Shader.cxx


echo "Linking .o files..."

g++ *.o -ldl -lglfw -o application

