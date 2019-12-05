echo Hello;
cd ./source;
make clean;
make;
xterm -e 'pwd;valgrind ../bin/app.exe; read';
