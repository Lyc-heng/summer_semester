# -*- coding: utf-8 -*-
import sys, time, random, math, pygame,locale,datetime
from pygame.locals import *
from sys import exit
import menu
import gamemap
import trap
import gameisover
import meetobstacle
import produceMonster
import MyLibrary
import crashbrick
import music

#关于马里奥动作的精灵类
#image和rect是sprite自己带着的函数参数，每次更新多会调用
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
#************************************************************************
    

menu.Start_menu()

SCREEN_SIZE = (800, 600)

background_image_filename = 'background.png'
stand_right = 'Mario Stand right.png'
stand_left = 'Mario Stand left.png'
monster = 'Goomba Dead.png'
coin1 = 'Coin_title.png'
BRICK = 'Brick World 1.png'
BLOCK = 'Empty Block.png'
mush = 'Mushroom.png'
flow = 'flower.png'
my_font = pygame.font.Font("New Super Mario Font U.ttf", 32)
end_flag = 'Flag.png'
pygame.mixer.init()
death_au = pygame.mixer.Sound("death.wav")
out_time_au = pygame.mixer.Sound("out_of_time.wav")
world_clear_au = pygame.mixer.Sound("world_clear.wav")
world_au = pygame.mixer.Sound("World 1.ogg")
coin_au = pygame.mixer.Sound("coin.wav")
jump_au = pygame.mixer.Sound("Jump.wav")
Mushroom_au = pygame.mixer.Sound("Mushroom.wav")
Power_up_au = pygame.mixer.Sound("powerup.wav")
kick_au = pygame.mixer.Sound("kick.wav")
death_sound = music.Music(death_au)
out_time_sound = music.Music(out_time_au)
world_clear_sound = music.Music(world_clear_au)
world_sound_sound = music.Music(world_au)
coin_sound = music.Music(coin_au)
jump_sound = music.Music(jump_au)
mushroom_sound = music.Music(Mushroom_au)
Power_up_sound = music.Music(Power_up_au)
kick_sound = music.Music(kick_au)


pygame.init()
screen = pygame.display.set_mode(SCREEN_SIZE, 0, 32)
pygame.display.set_caption("超级马里奥")
framerate = pygame.time.Clock()

#向右跑时精灵组的建立
RMarioR = MySprite(screen)
RMarioR.load("Mario Run right.png", 0, 505,34, 34, 4)
group1 = pygame.sprite.Group()
group1.add(RMarioR)

#向左跑时精灵组的建立
LMarioL = MySprite(screen)
LMarioL.load("Mario Run left.png", 0, 0,34, 34, 4)
group2 = pygame.sprite.Group()
group2.add(LMarioL)

#向右跳时精灵组的建立
JMarioR = MySprite(screen)
JMarioR.load("Mario Jump Right.png", 0, 0,34, 34, 2)
group3 = pygame.sprite.Group()
group3.add(JMarioR)

#向左跳时精灵组的建立
JMarioL = MySprite(screen)
JMarioL.load("Mario Jump Left.png", 0, 0, 34, 34, 2)
group4 = pygame.sprite.Group()
group4.add(JMarioL)

#怪物动画
Goomba1 = MySprite(screen)
Goomba1.load("Goomba.png", 800, 505, 32, 32,2)
group6 = pygame.sprite.Group()
group6.add(Goomba1)

Goomba2 = MySprite(screen)
Goomba2.load("Goomba.png", 0, 0, 32, 32,2)
group7 = pygame.sprite.Group()
group7.add(Goomba2)

Goomba3 = MySprite(screen)
Goomba3.load("Goomba.png", 0, 0, 32, 32,2)
group8 = pygame.sprite.Group()
group8.add(Goomba3)

#死亡动画精灵组的建立
DeathMario = MySprite(screen)
DeathMario.load("Mario Dead.png", 0, 0, 34, 34, 2)
group5 = pygame.sprite.Group()
group5.add(DeathMario)

#第一个问号箱子
price1 = MySprite(screen)
group9 = pygame.sprite.Group()
group9.add(price1)

#第二个问号箱子
price2 = MySprite(screen)
group11 = pygame.sprite.Group()
group11.add(price2)

#第三个问号箱子
price3 = MySprite(screen)
group12 = pygame.sprite.Group()
group12.add(price3)

#第四个问号箱子
price4 = MySprite(screen)
group13 = pygame.sprite.Group()
group13.add(price4)

#第五个问号箱子
price5 = MySprite(screen)
group14 = pygame.sprite.Group()
group14.add(price5)

#第六个问号箱子
price6 = MySprite(screen)
group15 = pygame.sprite.Group()
group15.add(price6)
#金币出现的连续动画
price_a = MySprite(screen)
#price_a.load("a1.png", 0, 0, 32, 100, 4)
group10 = pygame.sprite.Group()
group10.add(price_a)

#马里奥的奔跑动画是用精灵实现的，但站立是直接画上去的，所以用了一下两个变量来存位置
standx = 0 #马里奥的X
standy = 505 #马里奥的Y
direction_oldflag = 0 #之前的运动的方向
direction_flag = 0 #代表之前运动的方向，0代表右边，1代表左边
player_jumping = False #代表是否玩家进行了起跳
jump_vel = 0 #下落的加速度
get_trap = False #代表玩家已经掉入陷阱
death_animation = False #代表死亡动画是否开始播放
death_jump = -10 #死亡时，代表向上的速度
can_right_move = True #可以向右走
can_left_move = True #可以向左走
isHigh = False #代表是否在高处
High_jump = False #代表是否是在管子上起跳
pipe = 1 #代表是几号管子
isfall = False #用来解决穿管子的BUG
monster_number = 0#代表产生怪物的数量
M_number = -1 #代表怪物的号码
p_M1 = False#一下几个变量为判定怪物出现时的变量
p_M2 = False
p_M3 = False
p_M4 = False
p_M5 = False
p_M6 = False
monste_direction = 1 #代表之前运动的方向，0代表右边，1代表左边
monste_direction1 = 1 #代表之前运动的方向，0代表右边，1代表左边
monste_direction2 = 1 #代表之前运动的方向，0代表右边，1代表左边
death_flag = 0#用于让怪物掉下悬崖
death_flag1 = 0#用于让怪物掉下悬崖
monste_death = False#怪物死亡
monste1_death = False#怪物2死亡
monste2_death = False#怪物3死亡
touch_monster = False #代表是否接触了怪物
touch_death = False#代表是否开始播放接触怪物时死亡的动画
score_number = ['000000','000001','000002','000003','000004','000005','000006',
                '000006','000007','000008','000008','000009','000010','000011','000012','000013','000014','0000015','000016',
                '000017','000018','000019','000020']
score = 0
score_number1 = ['00','01','02','03','04','05','06','07','08','09','10','11','12','13','14','15','16','17','18','19','20','21','22','23']
score1 = 0
old = 0 #上一次时间的秒数
new = 0 #这一次时间的秒数
time = 400 #游戏总时间，一旦时间完毕，游戏结束
brick_flag = 800 #为了让砖块能保持相对位置
mushroom_price = False#蘑菇的相关变量
mushroom_x = 0
mushroom_y = 0
mushroom_jump_flag = 0
mushroom_meet_o = False#蘑菇遇到障碍物
banner_x = 800#关于终点旗子的变量
banner_y = 200
meet_brick =False
color_egg = 5#隐藏金币的变量
music_flag = 1

crash = False
crash1 = False
crash2 = False
crash3 = False
crash4 = False
crash5 = False
crash6 = False
crash7 = False
crash8 = False
pip = 0#解决管子和砖块冲突的BUG
can_right_move1 = True #可以向右走
can_left_move1 = True #可以向左走
isHigh1 = False #代表是否在高处
High_jump1 = False #代表是否是在管子上起跳

can_right_move2 = True #可以向右走
can_left_move2 = True #可以向左走
isHigh2 = False #代表是否在高处
High_jump2 = False #代表是否是在管子上起跳

can_right_move3 = True #可以向右走
can_left_move3 = True #可以向左走
isHigh3 = False #代表是否在高处
High_jump3 = False #代表是否是在管子上起跳

can_right_move4 = True #可以向右走
can_left_move4 = True #可以向左走
isHigh4 = False #代表是否在高处
High_jump4 = False #代表是否是在管子上起跳

can_right_move5 = True #可以向右走
can_left_move5 = True #可以向左走
isHigh5 = False #代表是否在高处
High_jump5 = False #代表是否是在管子上起跳

can_right_move6 = True #可以向右走
can_left_move6 = True #可以向左走
isHigh6 = False #代表是否在高处
High_jump6 = False #代表是否是在管子上起跳

can_right_move7 = True #可以向右走
can_left_move7 = True #可以向左走
isHigh7 = False #代表是否在高处
High_jump7 = False #代表是否是在管子上起跳

get_price1 = False#解决金币动画的变量
get_price2 = False
get_price3 = False
get_price4 = False
get_price5 = False
get_price6 = False
price_number1 = 0
price_number2 = 0
price_number3 = 0
price_number4 = 0
price_number5 = 0
price_number6 = 0

eat_flower = False #是否吃了花 

flag_ani = False #碰了旗子的动画

#马里奥对着右边的图片
Mario_stand_right = pygame.image.load(stand_right).convert_alpha()
Mario_stand_left = pygame.image.load(stand_left).convert_alpha()
monster_death = pygame.image.load(monster).convert_alpha()
title_coin  = pygame.image.load(coin1).convert_alpha()
brick = pygame.image.load(BRICK).convert_alpha()
block = pygame.image.load(BLOCK).convert_alpha()
mushroom = pygame.image.load(mush).convert_alpha()
vitory = pygame.image.load(end_flag).convert_alpha()
flower = pygame.image.load(flow).convert_alpha()

Map = gamemap.MyMap(background_image_filename)
world_sound_sound.play_sound()
while True:
#游戏循环
    framerate.tick(30)
    ticks = pygame.time.get_ticks()
    
    for event in pygame.event.get():
        if event.type == QUIT:
            #接收到事件后退出
            exit()


    #和时间相关的函数
    now = datetime.datetime.now()
    new = now.second
    if new-old >=1 or new - old <=-1:
        old=new
        time -= 1
        
    #地图
    screen.blit(Map.bg, (Map.x, Map.y))
    #马里奥的分数
    screen.blit(my_font.render("MARIO",True,(0,0,0)),(50,30))
    screen.blit(my_font.render(score_number[score],True,(0,0,0)),(50,78))
    #马里奥的金币数
    screen.blit(title_coin,(250, 78))
    screen.blit(my_font.render(" × ",True,(0,0,0)),(270,78))
    screen.blit(my_font.render(score_number1[score1],True,(0,0,0)),(294,78))
    #关卡数
    screen.blit(my_font.render("WORLD",True,(0,0,0)),(450,30))
    screen.blit(my_font.render("1-1",True,(0,0,0)),(470,78))
    #时间
    screen.blit(my_font.render("TIME",True,(0,0,0)),(650,30))
    screen.blit(my_font.render(str(time),True,(0,0,0)),(650,78))
    keys = pygame.key.get_pressed()
#*******************地图上砖块的绘制
#第一片区域
    
    if standx - Map.x < 1100:
        #第一块砖
        can_right_move1, can_left_move1, isHigh1,crash1 = crashbrick.crashwherebrick(standx, standy, brick_flag -420 + Map.x, 380)
        if  price_number1 == 0 and not get_price1:
            price1.load("prices.png", brick_flag -420 + Map.x, 380, 32, 32, 3)
            group9.update(ticks)
            group9.draw(screen)
        elif get_price1:
            screen.blit(block, (brick_flag -420 + Map.x, 380))
        if can_right_move1 == False and can_left_move1 == False and jump_vel < 0 :
            jump_vel = 0
            price_number1 = 4
        #****************第一块砖的动画演示
        if price_number1 > 0 and not get_price1:
            if price_number1 == 4:
                price_a.load("a1.png", brick_flag -420 + Map.x, 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number1 -= 1
            if price_number1 == 0:
                get_price1 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh1 == True and player_jumping ==True and High_jump1 == False :
            player_jumping = False
            standy = 380-32
            High_jump1 = True
        if isHigh1 == False and player_jumping ==True and High_jump1 == True :
            High_jump1 = False
        if isHigh1 == False and player_jumping == False and standy !=505  :
            player_jumping = True
            jump_vel = 0
        #第二块砖
        can_right_move2, can_left_move2, isHigh2,crash2= crashbrick.crashwherebrick(standx, standy, brick_flag -300+ Map.x, 380)
        screen.blit(brick, (brick_flag -300 + Map.x, 380))
        if can_right_move2 == False and can_left_move2 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh2 == True and player_jumping ==True: #and High_jump2 == False:
            player_jumping = False
            standy = 380-32
            High_jump2 = True
        #if isHigh2 == False and player_jumping ==True and High_jump2 == True:
            #High_jump2 = False
        #if isHigh2 == False and player_jumping == False and standy !=505 and standx > brick_flag -332+ Map.x and standx < brick_flag -268+ Map.x:
            #player_jumping = True
            #jump_vel = 0
        #第三块砖
        can_right_move3, can_left_move3, isHigh3,crash3= crashbrick.crashwherebrick(standx, standy, brick_flag -268 + Map.x, 380)
        if  price_number2 == 0 and not get_price2:
            price2.load("prices.png", brick_flag -268 + Map.x, 380, 32, 32, 3)
            group11.update(ticks)
            group11.draw(screen)
        elif get_price2:
            screen.blit(block, (brick_flag -268 + Map.x, 380))
        if can_right_move3 == False and can_left_move3 == False and jump_vel < 0:
            jump_vel = 0
            price_number2 = 4
        #****************第三块砖的动画演示
        if price_number2 > 0 and not get_price2:
            if price_number2 == 4:
                price_a.load("a1.png", brick_flag -268 + Map.x, 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number2 -= 1
            if price_number2 == 0:
                get_price2 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh3 == True and player_jumping ==True: #and High_jump1 == False:
            player_jumping = False
            standy = 380-32
            High_jump3 = True
        #if isHigh1 == False and player_jumping ==True and High_jump1 == True:
            #High_jump1 = False
        #if isHigh1 == False and player_jumping == False and standy !=505 :
            #player_jumping = True
            #jump_vel = 0
        #第四块砖
        can_right_move4, can_left_move4, isHigh4,crash4= crashbrick.crashwherebrick(standx, standy, brick_flag -236+ Map.x, 380)
        screen.blit(brick, (brick_flag -236 + Map.x, 380))
        if can_right_move4 == False and can_left_move4 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh4 == True and player_jumping ==True: #and High_jump2 == False:
            player_jumping = False
            standy = 380-32
            High_jump4 = True
        #第五块砖
        can_right_move5, can_left_move5, isHigh5,crash5= crashbrick.crashwherebrick(standx, standy, brick_flag -204 + Map.x, 380)
        if  price_number3 == 0 and not get_price3:
            price3.load("prices.png", brick_flag -204 + Map.x, 380, 32, 32, 3)
            group12.update(ticks)
            group12.draw(screen)
        elif get_price3:
            screen.blit(block, (brick_flag -204 + Map.x, 380))
        if can_right_move5 == False and can_left_move5 == False and jump_vel < 0:
            jump_vel = 0
            price_number3 = 4
        #****************第五块砖的动画演示
        if price_number3 > 0 and not get_price3:
            if price_number3 == 4:
                price_a.load("a3.png", brick_flag -204 + Map.x, 380-68, 32, 100, 4)
                mushroom_sound.play_sound()
            group10.update(ticks)
            group10.draw(screen)
            price_number3 -= 1
            if price_number3 == 0:
                get_price3 = True
                mushroom_price = True
                mushroom_x = brick_flag -204 + Map.x
                mushroom_y = 380 -32
                mushroom_jump_flag = brick_flag -204 + Map.x+64
        #*************************************
        if isHigh5 == True and player_jumping ==True: #and High_jump1 == False:
            player_jumping = False
            standy = 380-32
            High_jump5 = True
        #第六块砖
        can_right_move6, can_left_move6, isHigh6,crash6= crashbrick.crashwherebrick(standx, standy, brick_flag -172+ Map.x, 380)
        screen.blit(brick, (brick_flag -172 + Map.x, 380))
        if can_right_move6 == False and can_left_move6 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh6 == True and player_jumping ==True: #and High_jump2 == False:
            player_jumping = False
            standy = 380 - 32
            High_jump6 = True
        #第七块砖
        can_right_move7, can_left_move7, isHigh7,crash7 = crashbrick.crashwherebrick(standx, standy, brick_flag -236+ Map.x, 260)
        if  price_number4 == 0 and not get_price4:
            price4.load("prices.png", brick_flag -236+ Map.x, 260, 32, 32, 3)
            group13.update(ticks)
            group13.draw(screen)
        elif get_price4:
            screen.blit(block, (brick_flag -236+ Map.x, 260))
        if can_right_move7 == False and can_left_move7 == False and jump_vel < 0:
            jump_vel = 0
            price_number4 = 4
        #****************第三块砖的动画演示
        if price_number4 > 0 and not get_price4:
            if price_number4 == 4:
                price_a.load("a1.png", brick_flag -236+ Map.x, 260-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number4 -= 1
            if price_number4 == 0:
                get_price4 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh7 == True and player_jumping ==True: #and High_jump1 == False:
            player_jumping = False
            standy = 260-32
            High_jump7 = True
#************************************************************
        if not can_right_move1 or not can_right_move2 or not can_right_move3 or not can_right_move4 or not can_right_move5 or not can_right_move6 or not can_right_move7:
            can_right_move1 = False
        if not can_left_move1 or not can_left_move2 or not can_left_move3 or not can_left_move4 or not can_left_move5  or not can_left_move6 or not can_left_move7:
            can_left_move1 = False
        if crash1 or crash2 or crash3 or crash4 or crash5 or crash6 or crash7:
            crash = True
#**************************************************************
    #第二块区域
    if standx - Map.x>1103*2.679 and standx - Map.x <1113*2.679:
        brick_flag = 1220
        get_price1 = False
        get_price2 = False
        get_price3 = False
        get_price4 = False
        price_number1 = 0
        price_number2 = 0
        price_number3 = 0
        price_number4 = 0
    if standx - Map.x >1150*2.679 and standx - Map.x <1500*2.679:
        #第一块砖
        can_right_move1, can_left_move1, isHigh1,crash1 = crashbrick.crashwherebrick(standx, standy, brick_flag -420 , 380)
        if keys[K_RIGHT] != 0 and standx == 400:
            brick_flag -= 5
        if  price_number1 == 0 and not get_price1:
            price1.load("prices.png", brick_flag -420 , 380, 32, 32, 3)
            group9.update(ticks)
            group9.draw(screen)
        elif get_price1:
            screen.blit(block, (brick_flag -420 , 380))
        if can_right_move1 == False and can_left_move1 == False and jump_vel < 0 :
            jump_vel = 0
            price_number1 = 4
        #****************第一块砖的动画演示
        if price_number1 > 0 and not get_price1:
            if price_number1 == 4:
                price_a.load("a1.png", brick_flag -420 , 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number1 -= 1
            if price_number1 == 0:
                get_price1 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh1 == True and player_jumping ==True and High_jump1 == False :
            player_jumping = False
            standy = 380-32
            High_jump1 = True
        if isHigh1 == False and player_jumping ==True and High_jump1 == True :
            High_jump1 = False
        if isHigh1 == False and player_jumping == False and standy !=505  :
            player_jumping = True
            jump_vel = 0
        #第二块砖*********************************************************
        can_right_move2, can_left_move2, isHigh2,crash2= crashbrick.crashwherebrick(standx, standy, brick_flag -452, 380)
        screen.blit(brick, (brick_flag -452, 380))
        if can_right_move2 == False and can_left_move2 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh2 == True and player_jumping ==True: #and High_jump2 == False:
            player_jumping = False
            standy = 380-32
            High_jump2 = True
        #第三块砖*******************************
        can_right_move4, can_left_move4, isHigh4,crash4= crashbrick.crashwherebrick(standx, standy, brick_flag -388, 380)
        screen.blit(brick, (brick_flag -388, 380))
        if can_right_move4 == False and can_left_move4 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh4 == True and player_jumping ==True: 
            player_jumping = False
            standy = 380-32
            High_jump4 = True
        #第四块砖********************************
        can_right_move5, can_left_move5, isHigh5,crash5= crashbrick.crashwherebrick(standx, standy, brick_flag -388, 220)
        screen.blit(brick, (brick_flag -388, 220))
        if can_right_move5 == False and can_left_move5 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh5 == True and player_jumping ==True: 
            player_jumping = False
            standy = 220-32
            High_jump5 = True
        #第五块砖********************************
        can_right_move6, can_left_move6, isHigh6,crash6= crashbrick.crashwherebrick(standx, standy, brick_flag -356, 220)
        screen.blit(brick, (brick_flag -356, 220))
        if can_right_move6 == False and can_left_move6 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh6 == True and player_jumping ==True: 
            player_jumping = False
            standy = 220 - 32
            High_jump6 = True
        #第六块砖***********************************
        can_right_move3, can_left_move3, isHigh3,crash3= crashbrick.crashwherebrick(standx, standy, brick_flag -324, 220)
        screen.blit(brick, (brick_flag -304, 220))
        if can_right_move3 == False and can_left_move3 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh3 == True and player_jumping ==True: 
            player_jumping = False
            standy = 220 - 32
            High_jump6 = True
        #第七块砖*********************************
        can_right_move7, can_left_move7, isHigh7,crash7= crashbrick.crashwherebrick(standx, standy, brick_flag -420, 220)
        screen.blit(brick, (brick_flag -420, 220))
        if can_right_move7 == False and can_left_move7 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh7 == True and player_jumping ==True: 
            player_jumping = False
            standy = 220 - 32
            High_jump7 = True
#*************************************************
        if not can_right_move1 or not can_right_move2 or not can_right_move3 or not can_right_move4 or not can_right_move5 or not can_right_move6 or not can_right_move7:
            can_right_move1 = False
        if not can_left_move1 or not can_left_move2 or not can_left_move3 or not can_left_move4 or not can_left_move5 or not can_left_move6 or not can_left_move7:
            can_left_move1 = False
        if crash1 or crash2 or crash3 or crash4 or crash5 or crash6 or crash7:
            crash = True
#*****************************************************
    #第三块区域
    if standx - Map.x>1501*2.679 and standx - Map.x <1510*2.679:
        brick_flag = 2380
        get_price1 = False
        get_price2 = False
        get_price3 = False
        get_price4 = False
        price_number1 = 0
        price_number2 = 0
        price_number3 = 0
        price_number4 = 0
    if standx - Map.x >1510*2.679 and standx - Map.x <2443*2.679:
        #第一块砖
        can_right_move1, can_left_move1, isHigh1,crash1 = crashbrick.crashwherebrick(standx, standy, brick_flag -1420 , 180)
        if keys[K_RIGHT] != 0 and standx == 400:
            brick_flag -= 5
        if  price_number1 == 0 and not get_price1:
            price1.load("prices.png", brick_flag -1420 , 180, 32, 32, 3)
            group9.update(ticks)
            group9.draw(screen)
        elif get_price1:
            screen.blit(block, (brick_flag -1420 , 180))
        if can_right_move1 == False and can_left_move1 == False and jump_vel < 0 :
            jump_vel = 0
            price_number1 = 4
        #****************第一块砖的动画演示
        if price_number1 > 0 and not get_price1:
            if price_number1 == 4:
                price_a.load("a1.png", brick_flag -1420 , 180-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number1 -= 1
            if price_number1 == 0:
                get_price1 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh1 == True and player_jumping ==True and High_jump1 == False :
            player_jumping = False
            standy = 180-32
            High_jump1 = True
        if isHigh1 == False and player_jumping ==True and High_jump1 == True :
            High_jump1 = False
        if isHigh1 == False and player_jumping == False and standy !=505  and (crash1  or crash2 or crash3 or crash4 or crash5 or crash6 or crash7):
            player_jumping = True
            jump_vel = 0
        #第二块砖
        screen.blit(brick, (brick_flag -1484, 180))
        screen.blit(brick, (brick_flag -1516, 180))
        screen.blit(brick, (brick_flag -1548, 180))
        screen.blit(brick, (brick_flag -1580, 180))
        #第二块砖
        can_right_move2, can_left_move2, isHigh2,crash2= crashbrick.crashwherebrick(standx, standy, brick_flag -1452, 180)
        screen.blit(brick, (brick_flag -1452, 180))
        if can_right_move2 == False and can_left_move2 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh2 == True and player_jumping ==True:
            player_jumping = False
            standy = 180-32
            High_jump2 = True
        #第三块砖
        can_right_move3, can_left_move3, isHigh3,crash3= crashbrick.crashwherebrick(standx, standy, brick_flag -1420 , 380)
        if  price_number2 == 0 and not get_price2:
            screen.blit(brick, (brick_flag -1420, 380))
        elif get_price2:
            screen.blit(block, (brick_flag -1420, 380))
        if can_right_move3 == False and can_left_move3 == False and jump_vel < 0:
            jump_vel = 0
            price_number2 = 4
        #****************第三块砖的动画演示
        if price_number2 > 0 and not get_price2:
            if price_number2 == 4:
                price_a.load("a1.png", brick_flag -1420, 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number2 -= 1
            if price_number2 == 0:
                get_price2 = True
                score1 += 1
                coin_sound.play_sound()
                if color_egg >0:
                    get_price2 = False
                    color_egg -= 1
        #*************************************
        if isHigh3 == True and player_jumping ==True:
            player_jumping = False
            standy = 380-32
            High_jump3 = True
        #第四块砖
        can_right_move4 ,can_left_move4, isHigh4,crash4= crashbrick.crashwherebrick(standx, standy, brick_flag -1270 , 380)
        if  price_number3 == 0 and not get_price3:
            price2.load("prices.png", brick_flag -1270 , 380, 32, 32, 3)
            group11.update(ticks)
            group11.draw(screen)
        elif get_price3:
            screen.blit(block, (brick_flag -1270, 380))
        if can_right_move4 == False and can_left_move4 == False and jump_vel < 0:
            jump_vel = 0
            price_number3 = 4
        #****************第三块砖的动画演示
        if price_number3 > 0 and not get_price3:
            if price_number3 == 4:
                price_a.load("a1.png", brick_flag -1270, 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number3 -= 1
            if price_number3 == 0:
                get_price3 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh4 == True and player_jumping ==True: 
            player_jumping = False
            standy = 380-32
            High_jump4 = True
        #第五块砖
        can_right_move5 ,can_left_move5, isHigh5,crash5= crashbrick.crashwherebrick(standx, standy, brick_flag -1120 , 380)
        if  price_number4 == 0 and not get_price4:
            price3.load("prices.png", brick_flag -1120 , 380, 32, 32, 3)
            group12.update(ticks)
            group12.draw(screen)
        elif get_price4:
            screen.blit(block, (brick_flag -1120, 380))
        if can_right_move5 == False and can_left_move5 == False and jump_vel < 0:
            jump_vel = 0
            price_number4 = 4
        #****************第三块砖的动画演示
        if price_number4 > 0 and not get_price4:
            if price_number4 == 4:
                price_a.load("a1.png", brick_flag -1120, 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number4 -= 1
            if price_number4 == 0:
                get_price4 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh5 == True and player_jumping ==True: 
            player_jumping = False
            standy = 380-32
            High_jump5 = True
            #第六块砖
        can_right_move6 ,can_left_move6, isHigh6,crash6= crashbrick.crashwherebrick(standx, standy, brick_flag -970 , 380)
        if  price_number5 == 0 and not get_price5:
            price4.load("prices.png", brick_flag -970 , 380, 32, 32, 3)
            group13.update(ticks)
            group13.draw(screen)
        elif get_price5:
            screen.blit(block, (brick_flag -970, 380))
        if can_right_move6 == False and can_left_move6 == False and jump_vel < 0:
            jump_vel = 0
            price_number5 = 4
    #****************第六块砖的动画演示
        if price_number5 > 0 and not get_price5:
            if price_number5 == 4:
                price_a.load("a1.png", brick_flag -970, 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number5 -= 1
            if price_number5 == 0:
                get_price5 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh6 == True and player_jumping ==True:
            player_jumping = False
            standy = 380-32
            High_jump6 = True
        #第七块砖
        can_right_move7 ,can_left_move7, isHigh7,crash7= crashbrick.crashwherebrick(standx, standy, brick_flag -1120 , 180)
        if  price_number6 == 0 and not get_price6:
            price5.load("prices.png", brick_flag -1120 , 180, 32, 32, 3)
            group14.update(ticks)
            group14.draw(screen)
        elif get_price6:
            screen.blit(block, (brick_flag -1120, 180))
        if can_right_move7 == False and can_left_move7 == False and jump_vel < 0:
            jump_vel = 0
            price_number6 = 4
        #****************第七块砖的动画演示
        if price_number6 > 0 and not get_price6:
            if price_number6 == 4:
                price_a.load("a1.png", brick_flag -1120, 180-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number6 -= 1
            if price_number6 == 0:
                get_price6 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh7 == True and player_jumping ==True:
            player_jumping = False
            standy = 380-32
            High_jump7 = True
        #第八块砖
        if standx - Map.x >1740*2.679 and standx - Map.x <2443*2.679:
            #3个砖块，3个精灵
            screen.blit(brick, (brick_flag -650, 150))
            screen.blit(brick, (brick_flag -628, 150))
            screen.blit(brick, (brick_flag -596, 150))
            screen.blit(brick, (brick_flag -564, 150))
            screen.blit(brick, (brick_flag -532, 150))
            screen.blit(brick, (brick_flag -450, 150))
            screen.blit(brick, (brick_flag -428, 150))
            screen.blit(brick, (brick_flag -396, 150))
            #第九块砖
            can_right_move2 ,can_left_move2, isHigh2,crash2= crashbrick.crashwherebrick(standx, standy, brick_flag -500 , 380)
            if  price_number1 == 0 and not get_price1:
                price1.load("prices.png", brick_flag -500 , 380, 32, 32, 3)
                group9.update(ticks)
                group9.draw(screen)
            elif get_price1 and eat_flower == False:
                screen.blit(flower, (brick_flag -500, 380-32))
            elif get_price1 and eat_flower :
                screen.blit(brick, (brick_flag -500, 380))
            if can_right_move2 == False and can_left_move2 == False and jump_vel < 0:
                jump_vel = 0
                price_number1 = 4
            #****************第九块砖的动画演示
            if price_number1 > 0 and not get_price1:
                if price_number1 == 4:
                    price_a.load("a2.png", brick_flag -500, 380-64, 32, 100, 4)
                group10.update(ticks)
                group10.draw(screen)
                price_number1 -= 1
                if price_number1 == 0:
                    get_price1 = True
        #*************************************
            if isHigh2 == True and player_jumping ==True:
                player_jumping = False
                standy = 380-32
                High_jump2 = True
                if get_price1:
                    eat_flower = True
                    screen.blit(my_font.render("200",True,(0,0,0)),(standx +16, standy))
            #第十块砖
            can_right_move3, can_left_move3, isHigh3,crash3= crashbrick.crashwherebrick(standx, standy, brick_flag -468, 380)
            screen.blit(brick, (brick_flag -468, 380))
            if can_right_move3 == False and can_left_move3 == False and jump_vel < 0:
                jump_vel = 0
            if isHigh3 == True and player_jumping ==True:
                player_jumping = False
                standy = 380-32
                High_jump3 = True
#*************************************************
        if not can_right_move1 or not can_right_move2 or not can_right_move3 or not can_right_move4 or not can_right_move5 or not can_right_move6 or not can_right_move7 :
            can_right_move1 = False
        if not can_left_move1 or not can_left_move2 or not can_left_move3 or not can_left_move4 or not can_left_move5 or not can_left_move6 or not can_left_move7 :
            can_left_move1 = False
        if crash1 or crash2 or crash3 or crash4 or crash5 or crash6 or crash7 or crash8:
            crash = True
#*****************************************************
    #第四块区域
    if standx - Map.x>2443*2.679 and standx - Map.x <2480*2.679:
        brick_flag = 1500
        get_price1 = False
        get_price2 = False
        get_price3 = False
        get_price4 = False
        price_number1 = 0
        price_number2 = 0
        price_number3 = 0
        price_number4 = 0
    if standx - Map.x >2480*2.679 and standx - Map.x <3200*2.679:
        #第一块砖
        can_right_move1, can_left_move1, isHigh1,crash1 = crashbrick.crashwherebrick(standx, standy, brick_flag -388 , 380)
        if keys[K_RIGHT] != 0 and standx == 400:
            brick_flag -= 5
        if  price_number1 == 0 and not get_price1:
            price1.load("prices.png", brick_flag -388 , 380, 32, 32, 3)
            group9.update(ticks)
            group9.draw(screen)
        elif get_price1:
            screen.blit(block, (brick_flag -388 , 380))
        if can_right_move1 == False and can_left_move1 == False and jump_vel < 0 :
            jump_vel = 0
            price_number1 = 4
        #****************第一块砖的动画演示
        if price_number1 > 0 and not get_price1:
            if price_number1 == 4:
                price_a.load("a1.png", brick_flag -388 , 380-68, 32, 100, 4)
            group10.update(ticks)
            group10.draw(screen)
            price_number1 -= 1
            if price_number1 == 0:
                get_price1 = True
                score1 += 1
                coin_sound.play_sound()
        #*************************************
        if isHigh1 == True and player_jumping ==True and High_jump1 == False :
            player_jumping = False
            standy = 380-32
            High_jump1 = True
        if isHigh1 == False and player_jumping ==True and High_jump1 == True :
            High_jump1 = False
        if isHigh1 == False and player_jumping == False and standy !=505  and (crash1  or crash2  or crash4 or crash5 ):
            player_jumping = True
            jump_vel = 0
    #第二块砖
        #第二块砖*********************************************************
        can_right_move2, can_left_move2, isHigh2,crash2= crashbrick.crashwherebrick(standx, standy, brick_flag -452, 380)
        screen.blit(brick, (brick_flag -452, 380))
        if can_right_move2 == False and can_left_move2 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh2 == True and player_jumping ==True: #and High_jump2 == False:
            player_jumping = False
            standy = 380-32
            High_jump2 = True
        #第三块砖*******************************
        can_right_move4, can_left_move4, isHigh4,crash4= crashbrick.crashwherebrick(standx, standy, brick_flag -356, 380)
        screen.blit(brick, (brick_flag -356, 380))
        if can_right_move4 == False and can_left_move4 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh4 == True and player_jumping ==True: 
            player_jumping = False
            standy = 380-32
            High_jump4 = True
        #第四块砖********************************
        can_right_move5, can_left_move5, isHigh5,crash5= crashbrick.crashwherebrick(standx, standy, brick_flag -420, 380)
        screen.blit(brick, (brick_flag -420, 380))
        if can_right_move5 == False and can_left_move5 == False and jump_vel < 0:
            jump_vel = 0
        if isHigh5 == True and player_jumping ==True: 
            player_jumping = False
            standy = 380-32
            High_jump5 = True
        if not can_right_move1 or not can_right_move2 or not can_right_move3 or not can_right_move4 or not can_right_move5 or not can_right_move6 or not can_right_move7 :
            can_right_move1 = False
        if not can_left_move1 or not can_left_move2 or not can_left_move3 or not can_left_move4 or not can_left_move5 or not can_left_move6 or not can_left_move7 :
            can_left_move1 = False
        if crash1 or crash2 or crash3 or crash4 or crash5 or crash6 or crash7 or crash8:
            crash = True
#1-6号代表管子，其他代表其他障碍物
    can_right_move, can_left_move, isHigh, pipe= meetobstacle.ismeet(standx - Map.x, standy, isfall)
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 1:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 2:
        player_jumping = False
        standy = 505-49*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 3:
        player_jumping = False
        standy = 505-63*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 4:
        player_jumping = False
        standy = 505-63*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 5:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 6:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    #*************************************************************
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 7:
        player_jumping = False
        standy = 505-16*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 8:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 9:
        player_jumping = False
        standy = 505-48*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 10:
        player_jumping = False
        standy = 505-64*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 11:
        player_jumping = False
        standy = 505-64*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 12:
        player_jumping = False
        standy = 505-48*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 13:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 14:
        player_jumping = False
        standy = 505-16*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 15:
        player_jumping = False
        standy = 505-16*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 16:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 17:
        player_jumping = False
        standy = 505-48*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 18:
        player_jumping = False
        standy = 505-64*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 19:
        player_jumping = False
        standy = 505-16*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 20:
        player_jumping = False
        standy = 505-32*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 21:
        player_jumping = False
        standy = 505-48*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 22:
        player_jumping = False
        standy = 505-64*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 23:
        player_jumping = False
        standy = 505-80*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 24:
        player_jumping = False
        standy = 505-96*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 25:
        player_jumping = False
        standy = 505-112*2.679
        High_jump = True
        pip = 10
        crash = False
    if isHigh == True and player_jumping ==True and High_jump == False and pipe == 26:
        player_jumping = False
        standy = 505-128*2.679
        High_jump = True
        pip = 10
        crash = False
    if pipe == -1 and pip != 0:
        pip -= 5
    if isHigh == False and player_jumping ==True and High_jump == True and  crash == False: #and pip !=0 :
        High_jump = False
    if isHigh == False and player_jumping == False and standy !=505 and pipe <=6 and crash == False: #and  pip !=0 :
        player_jumping = True
        jump_vel = 0
    #***************************************************************************************
    #******************************怪物的行动逻辑
    #*************在这写一个函数来判断是否可以产生怪物
#第一只怪兽
    M_number = produceMonster.produce(standx - Map.x)
    if M_number == 1 or p_M1:
        #******碰撞函数
        #attacker = None
        #attacker =  pygame.sprite.spritecollideany(Goomba1, group1)
        #list_collide = pygame.sprite.spritecollide(Goomba1,group_Mario,False);
        #if len(pygame.sprite.spritecollide(Goomba1,group_Mario,False)) >0 and standx == Goomba1.temp1 and standy >= 505-33*2.679:
            #get_trap == True
        p_M1 = True
        p_M2 = False
        p_M3 = False
        p_M4 = False
        p_M5 = False
        p_M6 = False
        if monster_number == 0:
            monster_number += 1
            monste_death = False
        
        if standx >= Goomba1.temp1 -32 and standx  < Goomba1.temp1  and standy > 505-30 and monste_death == False:
            touch_monster = True
        if standx > Goomba1.temp1 +32 and standx  <= Goomba1.temp1 +64 and standy > 505-30 and monste_death == False:
            touch_monster = True

        if standx >=Goomba1.temp1 - 20 and standx <= Goomba1.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste_death == False:
            monste_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba1.temp1, Goomba1.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))
        ##############
        if monste_death == False:
            Goomba1.Monster_Left_move(3)
            if standx== 400 and keys[K_RIGHT]:
                Goomba1.Monster_Left_move(5)
            group6.update(ticks)
            group6.draw(screen)

#第二只怪兽
    if M_number == 2 or p_M2:
        p_M1 = False
        p_M2 = True
        p_M3= False
        p_M4= False
        p_M5= False
        p_M6= False
        if monster_number == 1:
            Goomba1.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste_death = False
        
        if standx >= Goomba1.temp1 -32 and standx  < Goomba1.temp1  and standy > 505-32 and monste_death == False:
            touch_monster = True
        if standx > Goomba1.temp1 + 32 and standx  <= Goomba1.temp1 +64 and standy > 505-32 and monste_death == False:
            touch_monster = True

        if standx >=Goomba1.temp1 - 20 and standx <= Goomba1.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste_death == False:
            monste_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba1.temp1, Goomba1.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))
            
        if monste_death == False :
            m_right, m_left , no1, no2= meetobstacle.ismeet(Goomba1.temp1 - Map.x, Goomba1.temp2, isfall)
            if m_left == False:
                monste_direction = 0
            if m_right == False:
                monste_direction = 1
            if m_left ==True and monste_direction == 1 :
                Goomba1.Monster_Left_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba1.Monster_Left_move(4)
            elif m_right == True and monste_direction == 0 :
                Goomba1.Monster_Right_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba1.Monster_Left_move(5)
            group6.update(ticks)
            group6.draw(screen)

#第三只怪兽
    if (M_number == 2 or p_M2) and standx - Map.x >=650*2.679:
        p_M1 = False
        p_M2 = True
        p_M3= False
        p_M4= False
        p_M5= False
        p_M6= False
        if monster_number == 2:
            Goomba2.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste1_death = False
           
        if standx >= Goomba2.temp1 -32 and standx  < Goomba2.temp1  and standy > 505-32 and monste1_death == False:
            touch_monster = True
        if standx > Goomba2.temp1 +32 and standx  <= Goomba2.temp1 +64 and standy > 505-32 and monste1_death == False:
            touch_monster = True

        if standx >=Goomba2.temp1 - 20 and standx <= Goomba2.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste1_death == False:
            monste1_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba2.temp1, Goomba2.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))
            
        if monste1_death == False :
            m_right1, m_left1 , no1, no2= meetobstacle.ismeet(Goomba2.temp1 - Map.x, Goomba2.temp2, isfall)
            if m_left1 == False:
                monste_direction1 = 0
            if m_right1 == False:
                monste_direction1 = 1
            if m_left1 ==True and monste_direction1 == 1 :
                Goomba2.Monster_Left_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba2.Monster_Left_move(4)
            elif m_right1 == True and monste_direction1 == 0 :
                Goomba2.Monster_Right_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba2.Monster_Left_move(5)
            group7.update(ticks)
            group7.draw(screen)

#第四只怪兽
    if (M_number == 2 or p_M2) and standx - Map.x >=660*2.679:
        p_M1 = False
        p_M2 = True
        p_M3= False
        p_M4= False
        p_M5= False
        p_M6= False
        if monster_number == 3:
            Goomba3.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste2_death =False
        
        if standx >= Goomba3.temp1 -32 and standx  < Goomba3.temp1  and standy > 505-32 and monste2_death == False:
            touch_monster = True
        if standx > Goomba3.temp1 +32 and standx  <= Goomba3.temp1 +64 and standy > 505-32 and monste2_death == False:
            touch_monster = True

        if standx >=Goomba3.temp1 - 20 and standx <= Goomba3.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste2_death == False:
            monste2_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba3.temp1, Goomba3.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))
            
        if monste2_death == False :
            m_right2, m_left2 , no1, no2= meetobstacle.ismeet(Goomba3.temp1 - Map.x, Goomba3.temp2, isfall)
            if m_left2 == False:
                monste_direction2 = 0
            if m_right2 == False:
                monste_direction2 = 1
            if m_left2 ==True and monste_direction2 == 1 :
                Goomba3.Monster_Left_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba3.Monster_Left_move(4)
            elif m_right2 == True and monste_direction2 == 0:
                Goomba3.Monster_Right_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba3.Monster_Left_move(5)
            group8.update(ticks)
            group8.draw(screen)
#第五只怪兽
    if M_number == 3 or p_M3:
        p_M1 = False
        p_M2 = False
        p_M3= True
        p_M4= False
        p_M5= False
        p_M6= False
        if monster_number == 4:
            Goomba1.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            death_flag = 445
            monste_death = False
            
        if standx >= Goomba1.temp1 -32 and standx  < Goomba1.temp1  and standy > 505-32 and monste_death == False:
            touch_monster = True
        if standx > Goomba1.temp1 +32 and standx  <= Goomba1.temp1 +64 and standy > 505-32 and monste_death == False:
            touch_monster = True

        if standx >=Goomba1.temp1 - 20 and standx <= Goomba1.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste_death == False:
            monste_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba1.temp1, Goomba1.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste_death == False :
            if death_flag <= 0:
                Goomba1.temp2 +=2
                Goomba1.rect = Goomba1.temp1, Goomba1.temp2, Goomba1.temp3, Goomba1.temp4
            else:
                Goomba1.Monster_Left_move(3)
                death_flag -=3
                if standx == 400 and keys[K_RIGHT]:
                    Goomba1.Monster_Left_move(5)
            group6.update(ticks)
            group6.draw(screen)
#第六只怪兽
    if (M_number == 3 or p_M3)and standx - Map.x >= 1440*2.679:
        p_M1 = False
        p_M2 = False
        p_M3= True
        p_M4= False
        p_M5= False
        p_M6= False
        if monster_number == 5:
            Goomba2.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            death_flag1 = 445
            monste1_death = False
        
        if standx >= Goomba2.temp1 -32 and standx  < Goomba2.temp1  and standy > 505-32 and monste1_death == False:
            touch_monster = True
        if standx > Goomba2.temp1 +32 and standx  <= Goomba2.temp1 +64 and standy >= 505-32 and monste1_death == False:
            touch_monster = True

        if standx >=Goomba2.temp1 - 20 and standx <= Goomba2.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste1_death == False:
            monste1_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba2.temp1, Goomba2.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste1_death == False :
            if death_flag1 <= 0:
                Goomba2.temp2 +=2
                Goomba2.rect = Goomba2.temp1, Goomba2.temp2, Goomba2.temp3, Goomba2.temp4
            else:
                Goomba2.Monster_Left_move(3)
                death_flag1 -=3
                if standx == 400 and keys[K_RIGHT]:
                    Goomba2.Monster_Left_move(5)
            group7.update(ticks)
            group7.draw(screen)
        
#第七只怪兽
    if M_number == 4 or p_M4:
        p_M1 = False
        p_M2 = False
        p_M3= False
        p_M4= True
        p_M5= False
        p_M6= False
        if monster_number == 6:
            Goomba1.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste_death = False
        
        if standx >= Goomba1.temp1 -32 and standx  < Goomba1.temp1  and standy > 505-32 and monste_death == False:
            touch_monster = True
        if standx > Goomba1.temp1 +32 and standx  <= Goomba1.temp1 +64 and standy > 505-32 and monste_death == False:
            touch_monster = True

        if standx >=Goomba1.temp1 - 20 and standx <= Goomba1.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste_death == False:
            monste_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba1.temp1, Goomba1.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste_death == False :
            Goomba1.Monster_Left_move(3)
            if standx == 400 and keys[K_RIGHT]:
                Goomba1.Monster_Left_move(5)
            group6.update(ticks)
            group6.draw(screen)
#第八只怪兽
    if (M_number == 4 or p_M4)and standx - Map.x >= 1680*2.679:
        p_M1 = False
        p_M2 = False
        p_M3= False
        p_M4= True
        p_M5= False
        p_M6= False
        if monster_number == 7:
            Goomba2.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste1_death = False
            
        if standx >= Goomba2.temp1 -32 and standx  < Goomba2.temp1  and standy > 505-32 and monste1_death == False:
            touch_monster = True
        if standx > Goomba2.temp1 +32 and standx  <= Goomba2.temp1 +64 and standy > 505-32 and monste1_death == False:
            touch_monster = True

        if standx >=Goomba2.temp1 - 20 and standx <= Goomba2.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste1_death == False:
            monste1_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba2.temp1, Goomba2.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste1_death == False :
            Goomba2.Monster_Left_move(3)
            if standx == 400 and keys[K_RIGHT]:
                Goomba2.Monster_Left_move(5)
            group7.update(ticks)
            group7.draw(screen)
#第九只怪兽        
    if M_number == 5 or p_M5:
        p_M1 = False
        p_M2 = False
        p_M3= False
        p_M4= False
        p_M5= True
        p_M6= False
        if monster_number == 8:
            Goomba1.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste_death = False
            
        if standx >= Goomba1.temp1 -32 and standx  < Goomba1.temp1  and standy > 505-32 and monste_death == False:
            touch_monster = True
        if standx > Goomba1.temp1 +32 and standx  <= Goomba1.temp1 +64 and standy > 505-32 and monste_death == False:
            touch_monster = True

        if standx >=Goomba1.temp1 - 20 and standx <= Goomba1.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste_death == False:
            monste_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba1.temp1, Goomba1.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste_death == False :
            Goomba1.Monster_Left_move(3)
            if standx == 400 and keys[K_RIGHT]:
                Goomba1.Monster_Left_move(5)
            group6.update(ticks)
            group6.draw(screen)
#第十只怪兽
    if (M_number == 5 or p_M5)and standx - Map.x >= 1970*2.679:
        p_M1 = False
        p_M2 = False
        p_M3= False
        p_M4= False
        p_M5= True
        p_M6= False
        if monster_number == 9:
            Goomba2.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste1_death = False
            
        if standx >= Goomba2.temp1 -32 and standx  < Goomba2.temp1  and standy > 505-32 and monste1_death == False:
            touch_monster = True
        if standx > Goomba2.temp1 +32 and standx  <= Goomba2.temp1 +64 and standy > 505-32 and monste1_death == False:
            touch_monster = True
            
        if standx >=Goomba2.temp1 - 20 and standx <= Goomba2.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste1_death == False:
            monste1_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba2.temp1, Goomba2.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste1_death == False :
            Goomba2.Monster_Left_move(3)
            if standx == 400 and keys[K_RIGHT]:
                Goomba2.Monster_Left_move(5)
            group7.update(ticks)
            group7.draw(screen)
#第十一只怪兽        
    if M_number == 6 or p_M6:
        p_M1 = False
        p_M2 = False
        p_M3= False
        p_M4= False
        p_M5= False
        p_M6= True
        if monster_number == 10:
            Goomba1.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste_death = False
        
        if standx >= Goomba1.temp1 -32 and standx  < Goomba1.temp1  and standy > 505-32 and monste_death == False:
            touch_monster = True
        if standx > Goomba1.temp1 +32 and standx  <= Goomba1.temp1 +64 and standy > 505-32 and monste_death == False:
            touch_monster = True

        if standx >=Goomba1.temp1 - 20 and standx <= Goomba1.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste_death == False:
            monste_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba1.temp1, Goomba1.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste_death == False :
            m_right, m_left , no1, no2= meetobstacle.ismeet(Goomba1.temp1 - Map.x, Goomba1.temp2, isfall)
            if m_left == False:
                monste_direction = 0
            if m_right == False:
                monste_direction = 1
            if m_left ==True and monste_direction == 1 :
                Goomba1.Monster_Left_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba1.Monster_Left_move(4)
            elif m_right == True and monste_direction == 0 :
                Goomba1.Monster_Right_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba1.Monster_Left_move(5)
            group6.update(ticks)
            group6.draw(screen)
#第十二只怪兽       
    if (M_number == 6 or p_M6)and standx - Map.x >=2542*2.679:
        p_M1 = False
        p_M2 = False
        p_M3= False
        p_M4= False
        p_M5= False
        p_M6= True
        if monster_number == 11:
            Goomba2.load("Goomba.png", 800, 505, 32, 32,2)
            monster_number += 1
            monste1_death = False
            
        if standx >= Goomba2.temp1 -32 and standx  < Goomba2.temp1  and standy > 505-32 and monste1_death == False:
            touch_monster = True
        if standx > Goomba2.temp1 +32 and standx  <= Goomba2.temp1 +64 and standy > 505-32 and monste1_death == False:
            touch_monster = True

        if standx >=Goomba2.temp1 - 20 and standx <= Goomba2.temp1 + 52 and standy <=505 - 33 and standy >=505-40 and monste1_death == False:
            monste1_death = True
            kick_sound.play_sound()
            screen.blit(monster_death, (Goomba2.temp1, Goomba2.temp2))
            jump_vel = -8
            score +=1
            screen.blit(my_font.render("100",True,(0,0,0)),(standx +16, standy))

        if monste1_death == False :
            m_right1, m_left1 , no1, no2= meetobstacle.ismeet(Goomba2.temp1 - Map.x, Goomba2.temp2, isfall)
            if m_left1 == False:
                monste_direction1 = 0
            if m_right1 == False:
                monste_direction1 = 1
            if m_left1 ==True and monste_direction1 == 1 :
                Goomba2.Monster_Left_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba2.Monster_Left_move(4)
            elif m_right1 == True and monste_direction1 == 0 :
                Goomba2.Monster_Right_move(3)
                if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                    Goomba2.Monster_Left_move(5)
            group7.update(ticks)
            group7.draw(screen)
    #**************************************************
    #到达终点时的动画
    if standx - Map.x >=3023*2.679:
        screen.blit(vitory, (banner_x, banner_y))
        if keys[K_RIGHT] != 0 and standx == 400 and standx - Map.x < 3168*2.679-34:
            banner_x -= 5
        if standx - Map.x >= 3168*2.679-34 and standy >= 505-16:
            can_right_move = False
        if standx - Map.x >= 3168*2.679-17 and standy <= 505-16:
            can_right_move = False
            flag_ani = True
            
    #关于朝右时的运动动画
    if keys[K_RIGHT] == 0 and direction_flag == 0 and player_jumping == False and flag_ani== False and get_trap == False and touch_monster == False:
        screen.blit(Mario_stand_right, (standx, standy))
    if keys[K_RIGHT] != 0 and player_jumping == False and get_trap == False and touch_monster == False and flag_ani== False:
        RMarioR.load("Mario Run right.png", standx, standy,34, 34, 4)
        if can_right_move == True and can_right_move1 == True:
            RMarioR.updateRect_Right(5)
        else :
            RMarioR.updateRect_Right(0)
        if trap.istrap(standx - Map.x, standy):
            get_trap = True
        else:
            group1.update(ticks)
            group1.draw(screen)
        direction_flag = 0
        direction_oldflag = direction_flag
        standx = RMarioR.temp1
        standy = RMarioR.temp2
    if keys[K_RIGHT] != 0 and RMarioR.temp1 == 400 and player_jumping ==False and touch_monster == False and get_trap ==False and can_right_move == True:
        Map.Mario_Move(5)

    #关于朝左时的运动动画
    if keys[K_LEFT] ==0 and direction_flag == 1 and player_jumping ==False and  flag_ani== False and get_trap ==False and touch_monster == False:
        screen.blit(Mario_stand_left, (standx, standy))
    if keys[K_LEFT] != 0 and player_jumping ==False and get_trap ==False and touch_monster == False and flag_ani== False:
        LMarioL.load("Mario Run left.png", standx, standy,34, 34, 4)
        if can_left_move == True and can_left_move1 == True:
            LMarioL.updateRect_Left(5)
        else:
            LMarioL.updateRect_Left(0)
        if trap.istrap(standx - Map.x, standy):
            get_trap = True
        else :
            group2.update(ticks)
            group2.draw(screen)
        direction_flag = 1
        direction_oldflag = direction_flag
        standx = LMarioL.temp1
        standy = LMarioL.temp2

    #按下空格键时，将起跳变量和速度初始化
    if keys[K_SPACE] !=0 and player_jumping == False and direction_flag == 0 and flag_ani== False and get_trap == False and touch_monster == False:
        player_jumping = True
        jump_vel = -12
        JMarioR.load("Mario Jump Right.png", standx, standy,34, 34, 2)
        jump_sound.play_sound()
    elif keys[K_SPACE] !=0 and player_jumping == False and direction_flag == 1 and flag_ani== False and get_trap == False and touch_monster == False:
        player_jumping = True
        jump_vel = -14
        JMarioL.load("Mario Jump Left.png", standx, standy,34, 34, 2)
        jump_sound.play_sound()
        
    if player_jumping and get_trap == False and touch_monster == False:
        if jump_vel <0:
            jump_vel += 0.4
            isfall = False
        elif jump_vel >=0 :
            jump_vel += 0.8
            isfall = True

        #把想要跳的方向进行重新设置
        if keys[K_RIGHT] != 0 :
            direction_flag = 0
        elif keys[K_LEFT] != 0:
            direction_flag = 1

        #右跳操作
        if keys[K_RIGHT] and direction_flag == 0 :
            JMarioR.load("Mario Jump Right.png", standx, standy,34, 34, 2)
            if can_right_move == True and can_right_move1 == True:
                JMarioR.updateRect_Right(5)
            else:
                JMarioR.updateRect_Right(0)
            JMarioR.updateRect_jump(jump_vel)
            group3.update(ticks)
            group3.draw(screen)
            direction_oldflag = direction_flag
            standx = JMarioR.temp1
            standy = JMarioR.temp2
            if standx ==400 and can_right_move == True and can_right_move1 == True:
                Map.Mario_Move(5)
        elif direction_flag == 0:
            JMarioR.updateRect_jump(jump_vel)
            group3.update(ticks)
            group3.draw(screen)
            direction_oldflag = direction_flag
            standx = JMarioR.temp1
            standy = JMarioR.temp2

        #左跳操作
        if keys[K_LEFT] and direction_flag == 1 :
            JMarioL.load("Mario Jump Left.png", standx, standy,34, 34, 2)
            if can_left_move ==True and can_left_move1 ==True:
                JMarioL.updateRect_Left(5)
            else:
                JMarioL.updateRect_Left(0)
            JMarioL.updateRect_jump(jump_vel)
            group4.update(ticks)
            group4.draw(screen)
            direction_oldflag = direction_flag
            standx = JMarioL.temp1
            standy = JMarioL.temp2
        elif direction_flag == 1:
            JMarioL.updateRect_jump(jump_vel)
            group4.update(ticks)
            group4.draw(screen)
            direction_oldflag = direction_flag
            standx = JMarioL.temp1
            standy = JMarioL.temp2

        #落到地面下时，让马里奥重回地面
        if JMarioR.temp2 > 505 and direction_flag == 0 :
            player_jumping = False
            isfall = False
            standy = 505
            JMarioR.temp2 = 505
            jump_vel = 0.0
            RMarioR.load("Mario Run right.png", standx, standy,34, 34, 4)
            if trap.istrap(standx - Map.x, standy):
                get_trap = True
        elif JMarioL.temp2 > 505 and direction_flag == 1:
            player_jumping = False
            isfall = False
            standy = 505
            JMarioL.temp2 = 505
            jump_vel = 0.0
            LMarioL.load("Mario Run left.png", standx, standy,34, 34, 4)
            if trap.istrap(standx - Map.x, standy):
                get_trap = True

    if get_trap == True :
        standy += 20
        if direction_flag == 0:
            screen.blit(Mario_stand_right, (standx, standy))
        if direction_flag == 1:
            screen.blit(Mario_stand_left, (standx, standy))
        if standy>600 and death_animation== False:
            death_animation = True
            death_jump = -50
            DeathMario.load("Mario Dead.png", standx, standy, 34, 34, 2)

    if death_animation:
        DeathMario.updateRect_jump(death_jump)
        group5.update(ticks)
        group5.draw(screen)
        if death_jump < 0:
            death_jump +=10
    if death_animation and death_jump == 0:
        world_sound_sound.play_pause()
        death_sound.play_sound()
        break

    if touch_monster == True and touch_death == False :
        touch_death = True
        death_jump = -10
        DeathMario.load("Mario Dead.png", standx, standy, 34, 34, 2)
        world_sound_sound.play_pause()
        death_sound.play_sound()

    if touch_death == True:
        DeathMario.updateRect_jump(death_jump)
        group5.update(ticks)
        group5.draw(screen)
        if death_jump < 0 :
            death_jump += 0.6
        if death_jump > 0:
            death_jump += 0.8
    if touch_death and DeathMario.temp2 >= 600:
        break
#蘑菇移动的动画演示
    if mushroom_price == True:
        screen.blit(mushroom, (mushroom_x, mushroom_y))
        mushroom_r, mushroom_l,none1,none2 = meetobstacle.ismeet(mushroom_x - Map.x, mushroom_y, isfall)
        if mushroom_r == True and not mushroom_meet_o :
            mushroom_x += 5
        else:
            mushroom_x -= 5
            mushroom_meet_o = True
            if standx== 400 and keys[K_RIGHT] and can_right_move == True:
                mushroom_x -= 5
        if mushroom_x >= mushroom_jump_flag and mushroom_y < 505:
            mushroom_y += 10
            if mushroom_y >=505:
                mushroom_y = 505
        if mushroom_x < standx +34 and mushroom_x > standx and standy == mushroom_y:
            mushroom_price = False
            score1 += 2
            Power_up_sound.play_sound()
            screen.blit(my_font.render("200",True,(0,0,0)),(standx +16, standy))

    if flag_ani and music_flag ==1:
        world_sound_sound.play_pause()
        world_clear_sound.play_sound()
        music_flag = 0
    if flag_ani and banner_x != 440:
        if standy > 450 and standy <505:
            screen.blit(my_font.render("200",True,(0,0,0)),(banner_x-10, banner_y+150))
        if standy > 350 and standy <450:
            screen.blit(my_font.render("400",True,(0,0,0)),(banner_x-10, banner_y+150))
        if standy < 350 :
            screen.blit(my_font.render("600",True,(0,0,0)),(banner_x-10, banner_y+150))
        banner_x -=5
        flag_ani = False
    if flag_ani and banner_x == 440:
        standx +=5
        RMarioR.load("Mario Run right.png", standx, standy,34, 34, 4)
        RMarioR.rect = standx,standy,RMarioR.temp3,RMarioR.temp4
        group1.update(ticks)
        group1.draw(screen)
    if standx - Map.x>3272*2.679:
        break
    if time <=100:
        world_sound_sound.play_pause()
        out_time_sound.play_sound()
        
    if time == 0 :
        break
    pygame.display.update()

    #刷新一下界面

gameisover.Gameisover(time)

    
