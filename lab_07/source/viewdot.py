import sys
import graphviz as gph


print("View graph")
a = gph.Graph(filename="../cache/" + sys.argv[2])

a.render("graph", "../cache")
