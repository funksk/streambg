#make them move every 30 secs?
#better idea - make them constantly move between a few states
#generate a bunch of random numbers (make this a dictionary)
#make a function that smoothly transitions between them every tick
#make sure this doesn't take up too many cycles?

#algorithm that evens out the whole thing
#like
#if 15 of these aren't greater than 500, re-randomize


#make it 3d or something? - shouldn't be hard

#add boarder for 4:3, 16:9, and for facecam

import pyglet
import time
import random
from datetime import datetime
from pyglet.gl import *
from pyglet.window import key

win = pyglet.window.Window(1280, 720, resizable=True)
#win = pyglet.window.Window(1920, 1080, resizable=True)
t = 33
dt = 0
fps = 24
lol = []
nlol = []
wlol = []
count = 0


def getlist(time):
    lx = []
    ly = []
    bx = []
    by = []
    tx = []
    ty = []
    rx = []
    ry = []
    print('precum',len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
    for x in range(0,time):
        random.seed(datetime.now())
        lx.append(random.uniform(-100,250))
        ly.append(random.uniform(-100,win.height+100))
        bx.append(random.uniform(-300,win.width+300))
        by.append(random.uniform(-100,150))
        tx.append(random.uniform(-300,win.width+300))
        ty.append(random.uniform(win.height-150,win.height+150))
        rx.append(random.uniform(win.width-250,win.width+50))
        ry.append(random.uniform(-100,win.height+100))
        print('cumming', len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
        print(lx)
    #print(lx,ly,bx,by,tx,ty,rx,ry)
    butts = [lx,ly,bx,by,tx,ty,rx,ry]
    return butts

def inc(temp, ntemp):
    for i in range(0,len(temp)):
        for j in range(0,t):
            if int(ntemp[i][j]) > int(temp[i][j]):
                temp[i][j]+=0.1
                #print('+',ntemp[i][j], temp[i][j])
            elif int(ntemp[i][j]) < int(temp[i][j]):
                temp[i][j]-=0.1
                #print('-',ntemp[i][j], temp[i][j])
            #elif int(ntemp[i][j]) == int(temp[i][j]):

    return temp


def udate(x):
    global count
    global lol
    global nlol
    global wlol
    count+=1
    print('hello!')
    #if count == (24*4):
    twlol = [[int(j) for j in i ]for i in wlol]
    tnlol = [[int(j) for j in i ]for i in nlol]
    if twlol == tnlol:
        lol = nlol
        nlol = getlist(t)
        wlol = lol
        count = 0
    wlol = inc(wlol,nlol)
    print(f'{x} seconds since last, {count/24} secs since switchup')

@win.event
def on_draw():
    #clear buffers
    glClear(GL_COLOR_BUFFER_BIT)

    #draw
    #glBegin(GL_POINTS)
    #draw outlines only
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    #glBegin(GL_TRIANGLES)
    #glBegin(GL_QUADS)
    #glBegin(GL_QUAD_STRIP)
    glBegin(GL_TRIANGLE_STRIP)
    print('lol = ', lol[0][0], '\nnlol = ', nlol[0][0], '\nwlol = ', wlol[0][0])
    for i in range(0,len(lol), 2):
        for j in range(0,t):
            glVertex2f(wlol[i][j],wlol[i+1][j])
    #print(lx,ly,bx,by,tx,ty,rx,ry)

    glEnd()

lol = getlist(t)
nlol = getlist(t)
wlol = lol
pyglet.clock.schedule_interval(udate, 1/fps)
pyglet.app.run()


while True:
    dt = clock.tick()
