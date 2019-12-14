mkdir bin
cd source
make
valgrind ../bin/app.exe < test.txt
# 3 3 1 2 0 0 0 3 4 0 0 3 1 1 0 1