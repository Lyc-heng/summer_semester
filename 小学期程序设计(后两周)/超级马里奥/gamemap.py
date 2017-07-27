import pygame
from pygame.locals import *
from sys import exit

#定义关于地图的滚动类
class MyMap(object) :
   def __init__(self, background_image_filename) :
      self.x = 0
      self.y = 0
      self.bg = pygame.image.load(background_image_filename).convert()
      self.bg_rect = self.bg.get_rect()
      self.bg = pygame.transform.smoothscale(self.bg,(int(self.bg_rect.width*2.679),int(self.bg_rect.height*2.679)))

   def Mario_Move(self, x) :
      self.x = self.x-x

   def map_update(self) :
      return self.x and self.y
