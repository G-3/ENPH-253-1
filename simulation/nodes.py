from Tkinter import *
import tkFont
import json

class Graph(object):
    def __init__(self, nodes):
        self.nodes = {nodes[i].get('id'): Node.fromData(nodes[i]) for i in range(len(nodes))
        for _,node in self.nodes.items():
              

    @classmethod
    def fromData(cls, data):
        return cls(**data)

    def draw(self, screen):
        for _,node in self.nodes.items():
            node.draw(screen)
	    print node.links
            for link in node.links:
                node2 = self.nodes.get(link)
               

class Node(object):
    """
    Note that x and y are given in relative units compared to the size of the board.
    """
    def __init__(self, id, name, x, y, links = []):
        self.id = id
        self.name = name
        self.x = x
        self.y = y
        self.links = links

    @classmethod
    def fromData(cls, data):
        return cls(**data)

    def draw(self, screen):
        width = screen.winfo_width()
        height = screen.winfo_height()
        cx = int(self.x*width)
        cy = int(self.y*height)
        print cx
        print cy
        screen.create_oval(cx-7, cy-7, cx+7, cy+7)
        helv18 = tkFont.Font(family='Helvetica', size=18, weight='bold')
        screen.create_text(cx+7, cy-7, text=self.name, activefill='green', font=helv18)

    def position(self):
        return (self.x, self.y)
    
    def absposition(self, width, height):
        return (self.x*width, self.y*height)


class Edge(object):
    def __init__(self, nodeA, nodeB):
        self.nodeA = nodeA
        self.nodeB = nodeB

    def draw(self, screen):
        nodelocx,nodelocy = node.absposition(screen.winfo_width(), screen.winfo_height())
        node2locx,node2locy = node2.absposition(screen.winfo_width(), screen.winfo_height())
        screen.create_line(nodelocx, nodelocy, node2locx, node2locy, width=4, activefill='green')


