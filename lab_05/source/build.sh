echo Hello;
cd ./source;
make clean;
make;
../bin/app.exe > ../bin/res.txt
# xterm -e 'pwd;valgrind ../bin/app.exe; read';
