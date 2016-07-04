import pygame
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
        width, height = screen.get_size()
        pygame.draw.circle(screen, (0, 0, 0),(int(self.x*width), int(self.y*height)),14,0)

    def position():
        return (self.x, self.y)
