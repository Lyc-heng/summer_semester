import pygame
from pygame.locals import *
from sys import exit

def Gameisover(time):
   background_image_filename = 'gameover.png'
   background_image_filename1 = 'timeover.png'

   SCREEN_SIZE = (800, 600)

   pygame.init()
   screen = pygame.display.set_mode(SCREEN_SIZE, 0, 32)
   background = pygame.image.load(background_image_filename).convert()
   background_rect = background.get_rect()
   background = pygame.transform.smoothscale(background,(int(background_rect.width*3.14),int(background_rect.height*2.84)))
   if time == 0:
      background = pygame.image.load(background_image_filename1).convert()
      background_rect = background.get_rect()
      background = pygame.transform.smoothscale(background,(int(background_rect.width*3.14),int(background_rect.height*2.84)))
   pygame.display.set_caption("游戏结束界面")
   
   while True:

      for event in pygame.event.get():
         if event.type == QUIT :
            exit()
            
      screen.blit(background, (0, 0))
      pygame.display.update()
