echo Hello;
cd ./source;
make clean;
make;
../bin/app.exe > ../examples/res.txt
# xterm -e 'pwd;valgrind ../bin/app.exe; read';
 