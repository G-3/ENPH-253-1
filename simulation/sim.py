from Tkinter import *
from nodes import Graph
import json

with open('resources/graph.json') as data_file:
    graph_data = json.load(data_file)

print(graph_data)
b_graph = Graph.fromData(graph_data)

master = Tk()

board = PhotoImage(file='resources/board.gif')

w = Canvas(master, width=board.width(), height=board.height())
w.pack()
w.update()

w.create_image(board.width()/2, board.height()/2, image=board)
b_graph.draw(w)
b_graph.printLinks()
b_graph.printDeadEnds()

master.mainloop()
