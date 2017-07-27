import pygame
from pygame.locals import *
from sys import exit


def ismeet(x, y, isFall):
   #第一个管子,返回的以此时向右走,向左走,是否在最高处
   if x >= 439*2.679 and x <= 445*2.679 and y <= 505 and y > 505-32*2.679:
      return False, True, False, 1
   elif x >= 445*2.679  and x < 475*2.679 and y <= 505-20*2.679 and y >= 505-38*2.679:
      return True, True, True, 1
   elif x >= 476*2.679 and x <= 478*2.679 and y <= 505 and y > 505-32*2.679:
      return True, False, False, 1
   
   #第二个管子
   if x >= 600*2.679 and x <= 606*2.679 and y <= 505 and y > 505-49*2.679:
      return False, True, False, 2
   elif x >=606*2.679 and x < 636*2.679 and y <= 505-43*2.679 and y >=505-55*2.679:
      return True, True, True, 2
   elif x >= 637*2.679 and x <= 639*2.679 and y<=505 and y > 505-49*2.679:
      return True, False, False, 2

   #第三个管子
   if x >= 728*2.679 and x <= 734*2.679 and y <= 505 and  y > 505-63*2.679:
      return False, True, False, 3
   elif x >= 734*2.679 and x < 764*2.679 and y <= 505-57*2.679 and y >= 505-69*2.679:
      return True, True, True, 3
   elif x >=765*2.679 and x <= 767*2.679 and y <= 505 and y > 505-63*2.679:
      return True, False, False, 3

   #第四个管子
   if x >= 904*2.679 and x <= 910*2.679 and y <= 505 and y > 505-63*2.679:
      return False, True, False, 4
   elif x >= 910*2.679 and x < 940*2.679 and y <= 505-57*2.679 and y >=505-69*2.679:
      return True, True, True, 4
   elif x >=941*2.679 and x <= 943*2.679 and y <= 505 and y > 505-63*2.679:
      return True, False, False, 4

   #第五个管子
   if x >= 2600*2.679 and x <= 2606*2.679 and y <= 505 and y > 505-32*2.679:
      return False, True, False, 5
   elif x >= 2606*2.679 and x < 2636*2.679 and y <= 505-32*2.679 and y >= 505-38*2.679:
      return True, True, True, 5
   elif x >= 2637*2.679 and x <= 2639*2.679 and y <=505 and y > 505-32*2.679:
      return True, False, False, 5

   if x >= 2856*2.679 and x <= 2862*2.679 and y <= 505 and y > 505-32*2.679:
      return False, True, False, 6
   elif x >= 2862*2.679 and x < 2892*2.679 and y <= 505-26*2.679 and y >= 505-38*2.679:
      return True, True, True, 6
   elif x >= 2893*2.679 and x <= 2895*2.679 and y <=505 and y > 505-32*2.679:
      return True, False, False, 19
#************************第一个三角
   if x >= 2133*2.679 and x <= 2139*2.679 and y <= 505 and  y > 505-6*2.679 :
      return False, True, False, 7
   elif x >= 2139*2.679 and x < 2150*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return True, True, True, 7
   elif x >= 2144*2.679 and x < 2153*2.679 and y <= 505-22*2.679 and y >=505-32*2.679 and isFall == True:
      return False, True, False, 7

   if x >= 2150*2.679 and x <= 2151*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return False, True, True, 7
   elif x >= 2151*2.679 and x < 2164*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return True, True, True, 8
   elif x >= 2158*2.679 and x < 2167*2.679 and y <= 505-38*2.679 and y >=505-48*2.679 and isFall == True:
      return False, True, False, 8

   if x >= 2164*2.679 and x <= 2165*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return False, True, True, 8
   elif x >= 2165*2.679 and x < 2178*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return True, True, True, 9
   elif x >= 2172*2.679 and x < 2181*2.679 and y <= 505-54*2.679 and y >=505-64*2.679 and isFall == True:
      return False, True, False, 9

   if x >= 2178*2.679 and x <=2180*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return False, True, True, 9
   elif x >= 2180*2.679 and x <= 2204*2.679 and y <= 505-64*2.679 and y > 505-70*2.679:
      return True, True, True, 10
   elif x >= 2187*2.679 and x < 2196*2.679 and y <= 505-70*2.679 and y >=505-80*2.679 and isFall == True:
      return False, True, False, 10
   elif x >= 2204*2.679 and x <=2206*2.679 and y <=505 and y > 505-70*2.679:
      return True, False, False, 10

#**********************************第二个三角
   if x >=2229*2.679 and x <=2240*2.679 and y<=505 and y >505-64*2.679:
      return False, True, False, 11
   elif x >= 2231*2.679 and x <= 2256*2.679 and y <= 505-64*2.679 and y > 505-70*2.679:
      return True, True, True, 11
   elif x >= 2256*2.679 and x < 2258*2.679 and y <= 505-48*2.679 and y > 505-64*2.679:
      return True, False, True, 12

   if x >= 2253*2.679 and x <= 2273*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return True, True, True, 12
   elif x >= 2273*2.679 and x <2275*2.679 and y <= 505-32*2.679 and y > 505-48*2.679:
      return True, False, True, 13

   if x >= 2275*2.679 and x <= 2288*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return True, True, True, 13
   elif x >= 2288*2.679 and x <2290*2.679 and y <= 505- 16*2.679 and  y > 505-32*2.679:
      return True, False, True, 14

   if x >=2290*2.679 and x <=2303*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return True, True, True, 14
   elif x >= 2303*2.679 and x <=2305*2.679 and y <= 505 and y > 505-6*2.679:
      return True, False, False, 14

   #第三个三角
   if x >= 2357*2.679 and x <= 2359*2.679 and y <= 505 and  y > 505-6*2.679 :
      return False, True, False, 15
   elif x >= 2359*2.679 and x < 2372*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return True, True, True, 15
   elif x >= 2366*2.679 and x < 2175*2.679 and y <= 505-22*2.679 and y >=505-32*2.679 and isFall == True:
      return False, True, False, 15

   if x >= 2372*2.679 and x <= 2374*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return False, True, True, 15
   elif x >= 2374*2.679 and x < 2387*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return True, True, True, 16
   elif x >= 2381*2.679 and x < 2390*2.679 and y <= 505-38*2.679 and y >=505-48*2.679 and isFall == True:
      return False, True, False, 16

   if x >= 2387*2.679 and x <= 2389*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return False, True, True, 16
   elif x >= 2389*2.679 and x < 2402*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return True, True, True, 17
   elif x >= 2396*2.679 and x < 2405*2.679 and y <= 505-54*2.679 and y >=505-64*2.679 and isFall == True:
      return False, True, False, 17

   if x >= 2402*2.679 and x <=2404*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return False, True, True, 17
   elif x >= 2404*2.679 and x < 2444*2.679 and y <= 505-64*2.679 and y > 505-70*2.679:
      return True, True, True, 18
   elif x >= 2411*2.679 and x < 2420*2.679 and y <= 505-70*2.679 and y >=505-80*2.679 and isFall == True:
      return False, True, False, 18
   elif x >= 2446*2.679 and x <=2450*2.679 and y <=505 and y > 505-70*2.679:
      return True, False, False, 18

   #第四个三角
   if x >=2467*2.679 and x <=2488*2.679 and y<=505 and y >505-64*2.679:
      return False, True, False, 11
   elif x >= 2469*2.679 and x <= 2494*2.679 and y <= 505-64*2.679 and y > 505-70*2.679:
      return True, True, True, 11
   elif x >= 2494*2.679 and x < 2496*2.679 and y <= 505-48*2.679 and y > 505-64*2.679:
      return True, False, True, 12

   if x >= 2491*2.679 and x <= 2511*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return True, True, True, 12
   elif x >= 2511*2.679 and x <2513*2.679 and y <= 505-32*2.679 and y > 505-48*2.679:
      return True, False, True, 13

   if x >= 2513*2.679 and x <= 2526*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return True, True, True, 13
   elif x >= 2526*2.679 and x <2528*2.679 and y <= 505- 16*2.679 and  y > 505-32*2.679:
      return True, False, True, 14

   if x >=2528*2.679 and x <=2541*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return True, True, True, 14
   elif x >= 2541*2.679 and x <=2543*2.679 and y <= 505 and y > 505-6*2.679:
      return True, False, False, 14

   #第五个三角
   if x >= 2886*2.679 and x <= 2893*2.679 and y <= 505 and  y > 505-6*2.679 :
      return False, True, False, 19
   elif x >= 2893*2.679 and x < 2903*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return True, True, True, 19
   elif x >= 2900*2.679 and x < 2909*2.679 and y <= 505-22*2.679 and y >=505-32*2.679 and isFall == True:
      return False, True, False, 19

   if x >= 2903*2.679 and x <= 2905*2.679 and y <= 505-16*2.679 and y > 505-22*2.679:
      return False, True, True, 19
   elif x >= 2905*2.679 and x < 2918*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return True, True, True, 20
   elif x >= 2912*2.679 and x < 2921*2.679 and y <= 505-38*2.679 and y >=505-48*2.679 and isFall == True:
      return False, True, False, 20

   if x >= 2918*2.679 and x <= 2920*2.679 and y <= 505-32*2.679 and y > 505-38*2.679:
      return False, True, True, 20
   elif x >= 2920*2.679 and x < 2933*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return True, True, True, 21
   elif x >= 2927*2.679 and x < 2936*2.679 and y <= 505-54*2.679 and y >=505-64*2.679 and isFall == True:
      return False, True, False, 21

   if x >= 2933*2.679 and x <=2935*2.679 and y <= 505-48*2.679 and y > 505-54*2.679:
      return False, True, True, 21
   elif x >= 2935*2.679 and x <= 2948*2.679 and y <= 505-64*2.679 and y > 505-70*2.679:
      return True, True, True, 22
   elif x >= 2942*2.679 and x < 2951*2.679 and y <= 505-70*2.679 and y >=505-80*2.679 and isFall == True:
      return False, True, False, 22
   #后四个
   if x >= 2948*2.679 and x <=2950*2.679 and y <= 505-64*2.679 and y > 505-70*2.679:
      return False, True, True, 22
   elif x >= 2950*2.679 and x <= 2963*2.679 and y <= 505-80*2.679 and y > 505-86*2.679:
      return True, True, True, 23
   elif x >= 2957*2.679 and x < 2966*2.679 and y <= 505-86*2.679 and y >=505-96*2.679 and isFall == True:
      return False, True, False, 23

   if x >= 2963*2.679 and x <= 2965*2.679 and y <= 505-80*2.679 and y > 505-86*2.679:
      return False, True, True, 23
   elif x >= 2965*2.679 and x <= 2978*2.679 and y <= 505-96*2.679 and y > 505-102*2.679:
      return True, True, True, 24
   elif x >= 2972*2.679 and x < 2981*2.679 and y <= 505-102*2.679 and y >=505-112*2.679 and isFall == True:
      return False, True, False, 24

   if x >= 2978*2.679 and x <=2980*2.679 and y <= 505-96*2.679 and y > 505-102*2.679:
      return False, True, True, 24
   elif x >= 2980*2.679 and x <= 2993*2.679 and y <= 505-112*2.679 and y > 505-118*2.679:
      return True, True, True, 25
   elif x >= 2987*2.679 and x < 2996*2.679 and y <= 505-118*2.679 and y >=505-128*2.679 and isFall == True:
      return False, True, False, 25

   if x >= 2993*2.679 and x <=2995*2.679 and y <= 505-112*2.679 and y > 505-118*2.679:
      return False, True, True, 25
   elif x >= 2995*2.679 and x < 3035*2.679 and y <= 505-128*2.679 and y > 505-134*2.679:
      return True, True, True, 26
   elif x >= 3002*2.679 and x < 3011*2.679 and y <= 505-134*2.679 and y >=505-144*2.679 and isFall == True:
      return False, True, False, 26
   elif x >= 3035*2.679 and x <=3041*2.679 and y <=505 and y > 505-134*2.679:
      return True, False, False, 26
   
   return True, True, False, -1
