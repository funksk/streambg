#TODO
#Average function - averages out the distrobution evenly. if there's a super easy way to do this online, do it
#Automatic boarder algorithm - input resolution, it centers the boarder on the screen
#       bonus fun, change the wavy things on the sides to adhere to this change
#Changing colors based on mood maybe??

#render to mp4 for streaming??
#Add 3d functionality to this, just see how it looks. but this is a later thing.

#algorithm that evens out the whole thing
#like
#if 15 of these aren't greater than 500, re-randomize
#or just randomize the values that are already in it to +200 or -200 of each, without going out of their bounds
#sounds kind of complicated, but i'd just have to create a variable for each of the numbers.
#this could be helpful for later when making the boarder creator for making the side thingies adhere to that

import sys, getopt, pyglet, time, random, copy
from datetime import datetime
from pyglet.gl import *
from pyglet.window import key

win = pyglet.window.Window(1280, 720, resizable=True)
#win = pyglet.window.Window(1920, 1080, resizable=True)
t = 66
dt = 0
fps = 30        #frames per second
lol = []        #list of lists
nlol = []       #new list of lists
wlol = []       #working list of lists
count = 0       #current counter of frames
uplims = 1*60       #upper limit in seconds
uplimf = fps*uplims     #upper limit in frames
running = False     #to set wlol to lol for the first time
D = False           #3d toggle  -   add support later
sn = False          #16:9 false, 4:3 true
fccm = False        #facecam toggle
label = pyglet.text.Label('be right back', font_name='Times New Roman', font_size=36, x=win.width//2,y=win.height//2,anchor_x='center',anchor_y='center')

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
    #gonna have to change this for 4:3, 16:9... whatever
    for x in range(0,time):         #setting up boarders
        random.seed(datetime.now())
        lx.append(random.triangular(-100,350))
        ly.append(random.triangular(-100,win.height+100))
        bx.append(random.triangular(-300,win.width+300))
        by.append(random.triangular(-50,200))
        tx.append(random.triangular(-300,win.width+300))
        ty.append(random.triangular(win.height-150,win.height+100))
        rx.append(random.triangular(win.width-350,win.width+100))
        ry.append(random.triangular(-100,win.height+100))
        print('midst', len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
        print(lx)
    #print(lx,ly,bx,by,tx,ty,rx,ry)
    butts = [lx,ly,bx,by,tx,ty,rx,ry]
    return butts

#APPEARENTLY some F*** that wrote python thought that it would be a good idea to make 
#the f**** EQUAL SIGN CREATE A POINTER BETWEEN LISTS
#WHAT THE F***

def inc():      #i hate that I don't pass anything to this, but im not rewriting it
    for i in range(0,len(wlol)):
        for j in range(0,t):
            if int(nlol[i][j]) > int(wlol[i][j]):
                ut = nlol[i][j]-lol[i][j]
                wlol[i][j]=wlol[i][j]+(ut/uplimf)
            elif int(nlol[i][j]) < int(wlol[i][j]):
                ut = lol[i][j]-nlol[i][j]
                wlol[i][j]=wlol[i][j]-(ut/uplimf)

def udate(x):
    global count
    global lol
    global nlol
    global wlol
    global running
    global label
    #print('I was ', running)
    if running == False:
        running = True
        wlol=copy.deepcopy(lol)     #who thought this was a good idea
        print(f'lol = {lol}\nwlol = {wlol}')
    #print(f'previous to increment\nlol = {lol[0][0]}\nwlol = {wlol[0][0]}\n\n{len(wlol)} {len(nlol)}')
    count+=1
    if count == uplimf:
        lol = nlol
        nlol = getlist(t)
        wlol=copy.deepcopy(lol)     #monkeys with typewriters maybe
        #lol = getlist(t)
        print(alol)     
        count = 0
    inc()
    print(f'{x} seconds since last, {count/24} secs since switchup')#\ntwlol = {twlol}\ntnlol = {tnlol}')

@win.event
def on_draw():
    
    #clear buffers
    win.clear()
    glClear(GL_COLOR_BUFFER_BIT)
    label.draw()
    glColor3f(0.241, 0.139, .61)
    
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
            #print('hello!')
            glVertex2f(wlol[i][j],wlol[i+1][j])





    #glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)
    # glVertex2f()
    # glVertex2f()
    # glVertex2f()
    # glVertex2f()
    # glVertex2f()
    # glVertex2f()
    #glEnd()
    glEnd()
    #label.draw()

lol = getlist(t)
nlol = getlist(t)
pyglet.clock.schedule_interval(udate, 1/fps)
pyglet.app.run()

#not sure what to do here... ill implement later, just get the whole boarder thing working for now

def main():
    global D
    global sn
    global fccm
    try:
        opts, args = getopt.getopt(sys.argv,"h:3d:43:169:fccm:")
    except getopt.GetoptError as err:
      print(str(err))
      print(f'\n-h shows this screen\n-3d enables 3d mode\n-43 enables the 4:3 aspect ratio\n-169 enables 16:9 ratio(default)\n-fccm enables facecam')
      sys.exit(2)
    for opt, arg in opts:
        if opt in "-3d": D = True
        elif opt in "-43": sn = True
        elif opt in "-169": sn = False
        elif opt in "fccm": fccm = True

    while True:
        dt = clock.tick()

if __name__ == "__main__":
    main()



