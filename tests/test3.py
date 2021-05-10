#make them move every 30 secs?
#better idea - make them constantly move between a few states
#generate a bunch of random numbers (make this a dictionary)
#make a function that smoothly transitions between them every tick
#make sure this doesn't take up too many cycles?

#algorithm that evens out the whole thing
#like
#if 15 of these aren't greater than 500, re-randomize


#make it 3d or something? - shouldn't be hard
import pyglet
import time
import random
from datetime import datetime
from pyglet.gl import *
from pyglet.window import key

win = pyglet.window.Window(1280, 720, resizable=True)
#win = pyglet.window.Window(1920, 1080, resizable=True)
lx = []
ly = []
bx = []
by = []
tx = []
ty = []
rx = []
ry = []
t = 33

def getlist(time):
    for x in range(0,time):
        random.seed(datetime.now())
        lx.append(random.randint(-100,250))
        ly.append(random.randint(-100,win.height+100))
        bx.append(random.randint(-300,win.width+300))
        by.append(random.randint(-100,150))
        tx.append(random.randint(-300,win.width+300))
        ty.append(random.randint(win.height-150,win.height+150))
        rx.append(random.randint(win.width-250,win.width+50))
        ry.append(random.randint(-100,win.height+100))
    print(lx,ly,bx,by,tx,ty,rx,ry)

@win.event
def on_key_press(symbol, modifiers):
    if symbol == pyglet.window.key.SPACE:
        print('space pressed')
        t = random.randint(0,33)
        #win.clear()
        getlist(t)
        for x in range(0,t):
            glVertex2i(lx[x],ly[x])
        for x in range(0,t):
            glVertex2i(bx[x],by[x])
        for x in range(0,t):
            glVertex2i(tx[x],ty[x])
        for x in range(0,t):
            glVertex2i(rx[x],ry[x])



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
    #lx = ly = bx = by = tx = ty = rx = ry = []
    print('there')
    getlist(t)
    for x in range(0,t):
        glVertex2i(lx[x],ly[x])
    for x in range(0,t):
        glVertex2i(bx[x],by[x])
    for x in range(0,t):
        glVertex2i(tx[x],ty[x])
    for x in range(0,t):
        glVertex2i(rx[x],ry[x])
    print('here')
    #print(lx,ly,bx,by,tx,ty,rx,ry)

    glEnd()

pyglet.app.run()
