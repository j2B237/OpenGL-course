echo "Cleanup project....."
echo ""

rm *.o

echo "Compiling files..."

g++ -Wall -Werror -pedantic -c main.cxx
g++ -Wall -Werror -pedantic -c glad.c

echo ""
echo "Linking obj files ..."

g++ *.o -ldl -lglfw -o application

echo ""
echo "Done ..."


