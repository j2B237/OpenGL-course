echo "Cleanup project....."
echo ""

rm *.o

echo "Compiling files..."

g++ -Wall -Werror -pedantic -c main.cxx
g++ -Wall -Werror -pedantic -c glad.c
g++ -Wall -Werror -pedantic -c Shader.cxx
g++ -Wall -Werror -pedantic -c Texture2D.cxx

echo ""
echo "Linking obj files ..."

g++ *.o -ldl -lglfw -o application

echo ""
echo "Done ..."


