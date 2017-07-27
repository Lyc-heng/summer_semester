# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
from sys import exit

class MySprite(pygame.sprite.Sprite):
    def __init__(self, target):
        pygame.sprite.Sprite.__init__(self)
        self.target_surface = target
        self.image = None
        self.master_image = None
        self.rect = None
        self.topleft = 0,0
        self.frame = 0
        self.old_frame = -1
        self.frame_width = 1
        self.frame_height = 1
        self.first_frame = 0
        self.last_frame = 0
        self.columns = 1
        self.last_time = 0
        self.temp1 = 0
        self.temp2 = 0
        self.temp3 = 0
        self.temp4 = 0
        
    #初始化一开始的位置和相关数据
    def load(self, filename, inix, iniy, width, height, columns):
        self.master_image = pygame.image.load(filename).convert_alpha()
        self.frame_width = width
        self.frame_height = height
        self.rect = inix, iniy, inix+width, iniy+height
        self.temp1 = inix
        self.temp2 = iniy
        self.temp3 = inix+width
        self.temp4 = iniy+height
        self.columns = columns
        rect = self.master_image.get_rect()
        self.last_frame = (rect.width // width) * (rect.height // height) - 1

    #让人物移动到另外一个位置去
    def updateRect_Right(self, x):
        self.temp1 += x
        if self.temp1 >=400:
            self.temp1 = 400
        self.rect = self.temp1,self.temp2,self.temp3,self.temp4

    def updateRect_Left(self, x):
        self.temp1 -= x
        if self.temp1 < 0:
            self.temp1 = 0
        self.rect = self.temp1,self.temp2,self.temp3,self.temp4

    def updateRect_jump(self, x):
        self.temp2 += x
        self.rect = self.temp1,self.temp2,self.temp3,self.temp4

    def Monster_Left_move(self, x):
        self.temp1 -= x
        self.rect = self.temp1,self.temp2,self.temp3,self.temp4

    def Monster_Right_move(self, x):
        self.temp1 += x
        self.rect = self.temp1,self.temp2,self.temp3,self.temp4

    #关于帧数的更新
    def update(self, current_time, rate=60):
        if current_time > self.last_time + rate:
            self.frame += 1
            if self.frame > self.last_frame:
                self.frame = self.first_frame
            self.last_time = current_time

        if self.frame != self.old_frame:
            frame_x = (self.frame % self.columns) * self.frame_width
            frame_y = (self.frame // self.columns) * self.frame_height
            rect = ( frame_x, frame_y, self.frame_width, self.frame_height )
            self.image = self.master_image.subsurface(rect)
            self.old_frame = self.frame
