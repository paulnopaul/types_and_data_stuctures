import sys
import random

def main():
    n = sys.argv[1]
    if not n.isdigit():
        print("Wrong argument")
        return 1
    file = open("../examples/testfile.txt", "w")
    print("Generate file:", end=" ")
    n = int(n)
    for i in range(n):
        print(i + 1, end=" ")
        print(random.randint(0, 100), file=file)
    file.close()
    print("File generated")
    return 0
        

if __name__ == "__main__":
    main()
