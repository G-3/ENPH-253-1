from Tkinter import *
import tkFont
import json

class Graph(object):
    def __init__(self, nodes):
        # Assign the nodes to dictionary by ID
        self.nodes = {nodes[i].get('id'): Node.fromData(nodes[i]) for i in range(len(nodes))}
        self.edges = []
        # link the nodes
        for _,node in self.nodes.items():
            for link in node.links:
                self.edges.append(Edge(node, self.nodes[link[0]], link[1]))

    @classmethod
    def fromData(cls, data):
        return cls(**data)

    def draw(self, screen):
        for _,node in self.nodes.items():
            node.draw(screen)
	    print node.links
            for link in node.links:
                node2 = self.nodes.get(link[1])
            for edge in self.edges:
                edge.draw(screen);
    
    def printLinks(self):
        linkStr = ''
        i = 0
        for _,node in self.nodes.items():
            for link in node.links:
                i += 1
                linkStr += '{{ {}, {}, {} }},\n'.format(node.id, link[0], link[1])
        print '{{ {} }}'.format(linkStr) 
        print i

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
        screen.create_oval(cx-10, cy-10, cx+10, cy+10, fill='orange')

        helv16 = tkFont.Font(family='Helvetica', size=16, weight='bold')

        screen.create_text(cx+14, cy-7, text=self.name, activefill='green', font=helv16)
        screen.create_text(cx, cy, text='{}'.format(self.id), font=helv16)
        

    def position(self):
        return (self.x, self.y)
    
    def absposition(self, width, height):
        return (self.x*width, self.y*height)


class Edge(object):
    def __init__(self, nodeA, nodeB, orient):
        self.nodeA = nodeA
        self.nodeB = nodeB
        self.orient = orient

    def draw(self, screen):
        nodelocx,nodelocy = self.nodeA.absposition(screen.winfo_width(), screen.winfo_height())
        node2locx,node2locy = self.nodeB.absposition(screen.winfo_width(), screen.winfo_height())
        if(self.orient == 0):
            nodelocx = nodelocx-5
            node2locx = node2locx-5
            nodelocy = nodelocy+20
            node2locy = node2locy-27

        elif(self.orient == 1):
            nodelocx = nodelocx+15
            node2locx = node2locx-15
            nodelocy = nodelocy-5
            node2locy = node2locy-5

        elif(self.orient == 2):
            nodelocx = nodelocx+5
            node2locx = node2locx+5
            nodelocy = nodelocy-27
            node2locy = node2locy+20

        elif(self.orient == 3):
            nodelocx = nodelocx-15
            node2locx = node2locx+15
            nodelocy = nodelocy+5
            node2locy = node2locy+5
            
        screen.create_line(nodelocx, nodelocy, node2locx, node2locy, width=3, fill='blue', activefill='red', arrow=LAST)
        helv12 = tkFont.Font(family='Helvetica', size=12, weight='bold')
        screen.create_text((nodelocx+node2locx)/2, (nodelocy+node2locy)/2, text="{}".format(self.orient), activefill='green', font=helv12)


