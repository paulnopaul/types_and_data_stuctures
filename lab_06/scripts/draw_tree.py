from graphviz import Digraph
import sys


def main():
    dot = Digraph(comment='Binary Search Tree')
    null_count = 0

    if len(sys.argv) != 3:
        return 1
    
    treefile = open(sys.argv[1], "r")
    # print(sys.argv[1])

    for line in treefile:
        if (line[0] == 'E'):
            dot.node("Empty")
            break
           
        source, dest = line.split()
        # print(source, dest)

        dot.node(source)

        if dest == "NULL":
            dest += str(null_count)
            null_count += 1
            dot.node(dest, "NULL", shape="point")
            # print(dest)
        else:
            dot.node(dest)

        dot.edge(source, dest)

    treefile.close()

    # print(sys.argv[1], sys.argv[2])
    outfile = open(sys.argv[2], "w")
    
    # print(dot.source)
    outfile.write(dot.source)

    outfile.close()

    dot.render(sys.argv[2], view=True)

    return 0

if __name__ == "__main__":
    if main() == 1:
        print("Draw function failed")



