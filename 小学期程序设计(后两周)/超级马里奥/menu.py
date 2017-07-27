import pygame
from pygame.locals import *
from sys import exit

def Start_menu():
    #背景图片
    background_image_filename = 'Title Screen.PNG'

#屏幕大小，位图原大小512,480
    SCREEN_SIZE = (800,600)

#初始化背景标题
    pygame.init()
    screen = pygame.display.set_mode(SCREEN_SIZE, 0,32)
    background = pygame.image.load(background_image_filename).convert()
    background_rect = background.get_rect()
    background = pygame.transform.smoothscale(background,
                                          (int(background_rect.width*1.5625),int(background_rect.height*1.25)))
    pygame.display.set_caption("游戏开始界面")

    StartupImageFilename = 'Start.png'
    StartdownImageFilename = 'Start_down.png'
    EndupImageFilename = 'end.png'
    EnddownImageFilename = 'end_down.png'

#定义一个按钮类
    class Button(object):
        def __init__(self, upimage, downimage,position):
            self.imageUp = pygame.image.load(upimage).convert_alpha()
            self.imageDown = pygame.image.load(downimage).convert_alpha()
            self.position = position
            self.game_start = False

        def isOver(self):
            point_x,point_y = pygame.mouse.get_pos()
            x, y = self. position
            w, h = self.imageUp.get_size()
            
            in_x = x - w/2 < point_x < x + w/2
            in_y = y - h/2 < point_y < y + h/2
            return in_x and in_y

        def render(self):
            w, h = self.imageUp.get_size()
            x, y = self.position

            if self.isOver():
                screen.blit(self.imageDown, (x-w/2,y-h/2))
            else:
                screen.blit(self.imageUp, (x-w/2, y-h/2))

        def is_start(self):
            if self.isOver():
                b1,b2,b3 = pygame.mouse.get_pressed()
                if b1 == 1:
                    self.game_start = True
                
                        
    startbutton = Button(StartupImageFilename,StartdownImageFilename, (400,400))
    endbutton = Button(EndupImageFilename,EnddownImageFilename, (390,480))

    while True:

        for event in pygame.event.get():
            if event.type == QUIT :
                exit()

        screen.blit(background, (0, 0))

        startbutton.render()
        endbutton.render()

        startbutton.is_start()

        if startbutton.game_start ==True:
            break

        pygame.display.update()
