echo "Removing object files..."
rm ./*.o

echo "Building project..."


g++ -Wall -Werror -pedantic -c main.cxx 
g++ -Wall -Werror -pedantic -c glad.c
g++ -Wall -Werror -pedantic -c Shader.cxx

g++ *.o -ldl -lglfw -o application

