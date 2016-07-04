import pygame
from nodes import Graph
import json

with open('resources/graph.json') as data_file:
    graph_data = json.load(data_file)
print graph_data
b_graph = Graph.fromData(graph_data)

pygame.init()

board = pygame.image.load('resources/board.png')
screen = pygame.display.set_mode(board.get_rect().size)
board = board.convert()


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
    screen.blit(board, (0,0))
    b_graph.draw(screen)
    pygame.display.flip()

pygame.quit()
