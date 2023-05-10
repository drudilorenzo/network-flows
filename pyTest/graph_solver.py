import sys
import json
import networkx as nx
import matplotlib.pyplot as plt

# Get the name of the file to read from the command line

# If no filename is specified, end the program with an error message
if len(sys.argv) < 2:
    print("No json file specified.")
    exit(1)
    
# If more than one argument is specified, end the program with an error message
if len(sys.argv) > 2:
    print("Too many arguments, only filename accepted.")
    exit(1)
    
# Get the filename from the command line
filename = sys.argv[1]

# Create an empty directed graph
graph = nx.DiGraph()

# Read the graph from json file and store it
with open(filename) as f:
    js_graph = json.load(f)
    num_nodes = js_graph["Num_nodes"]
    
    # Add nodes to the graph with the attributes weight and capacity
    # Look to the example in the documentation for more information on the json format
    for edge in js_graph["Edges"]:
        graph.add_edge(edge["Source"], edge["Sink"], cost=edge["Cost"], capacity=edge["Capacity"]);
        
# Draw the graph
pos=nx.spring_layout(graph)
nx.draw_networkx(graph, pos, with_labels=True)

# Add the labels to the edges
cost=nx.get_edge_attributes(graph,'cost')
capacity=nx.get_edge_attributes(graph,'capacity')
labels = {}
for e in cost.keys():
    labels[e] = str(cost[e]) + " / " + str(capacity[e])
nx.draw_networkx_edge_labels(graph, pos, edge_labels=labels)

# Source node (the 0 node)
source = 0 

# Sink node (the max node)
sink = num_nodes - 1

# Compute the maximum flow. Default algorithm is highest-label preflow-push algorithm.
flow_value, flow_dict = nx.maximum_flow(graph, source, sink)
print("Maximum flow graph:\n" + str(flow_dict) + "\n")
print("Maximum flow value:\n" + str(flow_value) + "\n")

# Compute the minimum cost flow. Default algorithm is Edmonds-Karp
min_cost_flow = nx.max_flow_min_cost(graph, source, sink)
print("Minimum cost flow graph:\n" + str(min_cost_flow) + "\n")
min_cost = nx.cost_of_flow(graph, min_cost_flow)
print("Minimum cost flow cost:\n" + str(min_cost))

# Get the filename without the path and the extension
# e.g. "data/graph1.json" -> "graph1"
graph_name = filename.split('/')[-1].split('.')[0]

# Plot the graph using matplotlib
plt.axis('off')
plt.draw()
plt.get_current_fig_manager().set_window_title("Graph: " + graph_name)
plt.show()


