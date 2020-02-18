import sys
from graphviz import Source

f = open("./cache/" + sys.argv[1], "r")
text = f.read()
f.close()

a = Source(text, filename=sys.argv[1], directory="./cache/")

a.view()
