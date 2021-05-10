import pyglet
import random
from datetime import datetime
from pyglet.gl import *

win = pyglet.window.Window(1280, 720, resizable=True)
li = []
li2 = []
t = 50
def getlist(time):
    for x in range(0,time):
        random.seed(datetime.now())
        n = random.randint(0,1920)
        li.append(n)
        
    for x in range(0,time):
        random.seed(datetime.now())
        i = random.randint(0,1080)
        li2.append(i)
        
    return li, li2

@win.event
def on_draw():

    #clear buffers
    glClear(GL_COLOR_BUFFER_BIT)

    #draw
    #glBegin(GL_LINES)
    #glBegin(GL_LINE_STRIP)
    #glBegin(GL_POINTS)
    #glBegin(GL_LINE_LOOP)

    #draw outlines only
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    #glBegin(GL_TRIANGLES)
    glBegin(GL_TRIANGLE_STRIP)
    #glBegin(GL_TRIANGLE_FAN)
    #glVertex2i(50, 50)
    #glVertex2i(75,100)
    #glVertex2i(200,200)
    #glVertex2i(50,250)
    #glVertex2i(500,500)
    butts, butts2 = getlist(t)
    for x in range(0,t):
        glVertex2i(butts[x],butts2[x])

    glEnd()
    
#butts = [50, 75, 200, 50, 500]
#butts2 = [50, 100, 200, 250, 500]
#print(butts, butts2, poop)
pyglet.app.run()
