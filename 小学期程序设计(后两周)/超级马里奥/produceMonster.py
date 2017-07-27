import pygame
from pygame.locals import *
from sys import exit

def produce(x):
   if x > 200 and x < 360*2.679:
      return 1
   if x > 500*2.679 and x < 1200*2.679:
      return 2
   if x >1424*2.679 and x < 1650*2.679:
      return 3
   if x > 1650*2.679 and x < 1900*2.679:
      return 4
   if x > 1950*2.679 and x < 2300*2.679:
      return 5
   if x > 2532*2.679  and x < 3200*2.679:
      return 6
   return  -1
