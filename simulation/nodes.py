from Tkinter import *
import tkFont
import json

class Graph(object):
    def __init__(self, nodes):
        self.nodes = {nodes[i].get('id'): Node.fromData(nodes[i]) for i in range(len(nodes))}

    @classmethod
    def fromData(cls, data):
        return cls(**data)

    def draw(self, screen):
        for _,node in self.nodes.items():
            node.draw(screen)
            for link in node.links:
                node2 = self.nodes.get(link)
                screen.create_line()

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

    def position():
        return (self.x, self.y)
