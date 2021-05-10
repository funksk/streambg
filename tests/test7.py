#algorithm that evens out the whole thing
#like
#if 15 of these aren't greater than 500, re-randomize

#make it 3d or something? - shouldn't be hard

#add boarder for 4:3, 16:9, and for facecam

#add elasticity and accelleration?
#such as: has to get done in 1000 frames, so speed is setup according to
#some funciton newpoint-oldpoint*accelleration(something to do with frames)
#such that it is done just in time for the 1000 frames
#this could make some slower, some faster

#different colors
#I could just key it out with something like xplit or some program


#ONCE THIS IS DONE, MAKE A 3D VERSION!!, COULD LOOK COOL!

import pyglet
import time
import random
from datetime import datetime
from pyglet.gl import *
from pyglet.window import key

win = pyglet.window.Window(1280, 720, resizable=True)
#win = pyglet.window.Window(1920, 1080, resizable=True)
t = 9
dt = 0
fps = 24        #frames per second
lol = []        #list of lists
nlol = []       #new list of lists
wlol = []       #working list of lists
count = 0       #current counter of frames
uplims = 10       #upper limit in seconds
uplimf = fps*uplims     #upper limit in frames
running = False


def getlist(time):
    lx = []         #please dear god tell me there's a different way of doing this
    ly = []         #left
    bx = []         #bottom
    by = []
    tx = []         #top
    ty = []
    rx = []         #right
    ry = []
    #if one of these has not t/2 amount of floats that are above maxspread/2 (evenly distributed)
    #recalculate the one that doesn't have this
    print('pre',len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
    for x in range(0,time):         #setting up boarders
        random.seed(datetime.now())
        lx.append(random.uniform(-100,250))
        ly.append(random.uniform(-100,win.height+100))
        bx.append(random.uniform(-300,win.width+300))
        by.append(random.uniform(-100,150))
        tx.append(random.uniform(-300,win.width+300))
        ty.append(random.uniform(win.height-150,win.height+150))
        rx.append(random.uniform(win.width-250,win.width+50))
        ry.append(random.uniform(-100,win.height+100))
        print('midst', len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
        print(lx)
    #print(lx,ly,bx,by,tx,ty,rx,ry)
    butts = [lx,ly,bx,by,tx,ty,rx,ry]
    return butts

#I want these to get closer to each other until they are the same at exactly uplims
#i have to make it so that ut = 0 before upilms
#
#delta units/(fps*time)
#temp[i][j]+=ntemp[i][j]-temp[i][j]/(fps*uplims)


#i'm seeing the issue.... I need to store the initial constant rate of change... no I dont
#that's why we keep lol intact, as a reference point to grab the constant rate of change from
#and assign the maths intermediary to wlol, wtf
#now just find out why tf wlol is updating lol
#lol is updating somewhere in inc wtf??

#what the fuck is the point of passing variables to a function if it's gonna change
#the original fucking values. why the fuck is python so stupid

def inc(temp, ntemp, otemp):
    for i in range(0,len(temp)):
        for j in range(0,t):
            if int(ntemp[i][j]) > int(temp[i][j]):
                ut = ntemp[i][j]-otemp[i][j]
                temp[i][j]+=ut/uplimf
            elif int(ntemp[i][j]) < int(temp[i][j]):
                ut = otemp[i][j]-ntemp[i][j]
                temp[i][j]-=ut/uplimf
            #print(f'otemp = {otemp[i][j]} lol = {otemp[i][j]} temp = {temp[i][j]} wlol = {temp[i][j]}')
    print(f'otemp = {otemp[0][0]} lol = {otemp[0][0]} temp = {temp[0][0]} wlol = {temp[0][0]}')
            #print(f'{ntemp[0][0]}, {temp[0][0]}, {ut}')

    return temp


def udate(x):
    global count
    global lol
    global nlol
    global wlol
    global running
    print('I was ', running)
    if running == False:
        running = True
        wlol = lol
    #print('but now I am', running)
    print(f'previous to increment\nlol = {lol[0][0]}\nwlol = {wlol[0][0]}')
    count+=1
    #twlol = [[int(j) for j in i ]for i in wlol]
    #tnlol = [[int(j) for j in i ]for i in nlol]
    if count == uplimf:
        print('were at the limit, marty')
        lol = nlol
        nlol = getlist(t)
        wlol = lol
        count = 0
    wlol = inc(wlol,nlol,lol)
    print(f'{x} seconds since last, {count/24} secs since switchup')#\ntwlol = {twlol}\ntnlol = {tnlol}')

@win.event
def on_draw():
    #clear buffers
    glClear(GL_COLOR_BUFFER_BIT)

    #draw only the points
    #glBegin(GL_POINTS)
    #draw outlines only
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    glBegin(GL_TRIANGLES)
    #glBegin(GL_QUADS)
    #glBegin(GL_QUAD_STRIP)
    #glBegin(GL_TRIANGLE_STRIP)
    print('lol = ', lol[0][0], '\nnlol = ', nlol[0][0], '\nwlol = ', wlol[0][0])
    for i in range(0,len(lol), 2):
        for j in range(0,t):
            glVertex2f(wlol[i][j],wlol[i+1][j])
    #print(lx,ly,bx,by,tx,ty,rx,ry)

    glEnd()

lol = getlist(t)
nlol = getlist(t)
pyglet.clock.schedule_interval(udate, 1/fps)
pyglet.app.run()


while True:
    dt = clock.tick()
