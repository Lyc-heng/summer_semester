import pygame
from pygame.locals import *
from sys import exit

#1代表碰到了砖块的下方,2,3代表碰到了右边或左边，4代表飞到了砖块上面
def crashwherebrick(Mx, My, x, y):
   if Mx > x - 32 and Mx < x + 30 and My <= y + 42 and My >= y +30 :
      return False, False,False, True
   if Mx > x- 30 and Mx < x  and My < y + 32 and My > y - 30:
      return False, True, False,True
   if Mx > x  and Mx < x + 30 and My < y + 32 and My > y - 30:
      return True, False, False,True
   if Mx >=x - 32 and Mx <=x + 32 and My <= y -30 and My >= y - 40:
      return True,True,True,True
   return True, True, False,False
