#TODO
#Average function - averages out the distrobution evenly. if there's a super easy way to do this online, do it
#Automatic boarder algorithm - input resolution, it centers the boarder on the screen
#       bonus fun, change the wavy things on the sides to adhere to this change
#Antialiasing?? found some stuff online about that
#Changing colors based on mood maybe??
#render to mp4 for streaming??
#Add 3d functionality to this, just see how it looks. but this is a later thing.

#peep getlist later, chances are high that I messed it up
#combine xyjust, and getxy, and uncouple getlist from these. rewrite a buncha stuff and uncomplicate i think
#get any calculations out of draw function


#algorithm that evens out the whole thing
#like
#if 15 of these aren't greater than 500, re-randomize
#or just randomize the values that are already in it to +200 or -200 of each, without going out of their bounds
#sounds kind of complicated, but i'd just have to create a variable for each of the numbers.
#this could be helpful for later when making the boarder creator for making the side thingies adhere to that

import sys, getopt, pyglet, time, random, copy#, numpy
from datetime import datetime
from pyglet.gl import *
from pyglet.window import key

win = pyglet.window.Window(1280, 720, resizable=True)
#win = pyglet.window.Window(1920, 1080)
t = 33      #scale this value by how big the gap is between the walls and screen. make divisible by 3
dt = 0
fps = 30        #frames per second
lol = []        #list of lists
nlol = []       #new list of lists
wlol = []       #working list of lists
lims = {}       #dict of limits for each side of end vectors
scnl = []       #screen list DEBUG??
bx = [800, 600, True]   #resolution of box, then if to show or not
fccm = [200, 200, False] #resolution of facecam, then to show or not
count = 0       #current counter of frames
#uplims = 5*60       #upper limit in seconds
uplims = 1       #upper limit in seconds
uplimf = fps*uplims     #upper limit in frames
frm = True          #frame toggle
running = False     #to set wlol to lol for the first time
D = False           #3d toggle  -   add support later
frame = 0


'''
pass 't' value to list, which is the amount of vector loctions for each side of the board
returns random list of lists of coords for each side, according to what had been set for
the list of edge bounds from getxy
'''
def getlist(lims,time):
    lx = []         #please dear god tell me there's a different way of doing this
    ly = []         #left
    bx = []         #bottom
    by = []
    tx = []         #top
    ty = []
    rx = []         #right
    ry = []
    #if one of these has not t/2 amount of floats that are above maxspread/2 (evenly distributed)
    #recalculate the one that does't have this
    print('pre',len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
    #okay!! we're going to have to make these some values!
    for x in range(0,time):         #setting up boarders
        random.seed(datetime.now())     
        lx.append(random.uniform(lims['lx1'][0],lims['lx1'][1]))
        ly.append(random.uniform(lims['ly'][0],lims['ly'][1]))
        bx.append(random.uniform(lims['bx'][0],lims['bx'][1]))
        by.append(random.uniform(lims['by'][0],lims['by'][1]))
        tx.append(random.uniform(lims['tx'][0],lims['tx'][1]))
        ty.append(random.uniform(lims['ty'][0],lims['ty'][1]))
        rx.append(random.uniform(lims['rx'][0],lims['rx'][1]))
        ry.append(random.uniform(lims['ry'][0],lims['ry'][1]))
    #the average of these values should be like 50% of whatever full value is passed.
    #the function that we are looking for is not called evenly distributed
    #not sure what it is called though
        #print('midst', len(lx),len(ly),len(bx),len(by),len(tx),len(ty),len(rx),len(ry))
        #print(lx)
    #if any([lx,ly,bx,by,tx,ty,rx,ry]) :
    #print(lx,ly,bx,by,tx,ty,rx,ry)
    return [lx,ly,bx,by,tx,ty,rx,ry]

def getlims(x1, y1, x2, y2):
    td =  {'lx1': [-100,x1+50], 'ly': [-100,win.height+100], 'bx': [-300,win.width+300], 'by': [-100,y2+50], 'tx': [-300,win.width+300], 'ty': [y1-75,win.height+100], 'rx': [x2-50,win.width+100], 'ry': [-100,win.height+100]}
    return td

'''
randomizes list of lists that has already been randomized
should take a list of coords that was generated by getlims, and output some random numbers
that arent too far off from what was generated
but within the bounds of the xy for each side
returns the pesudo randomized list
'''

def randlist(tls, lims):
    d = dict((i,j) for i,j in enumerate(lims))
    print(d)
    for i in range(0,len(tls)):
        for j in range(0,len(tls[i])):
            tls[i][j] = random.uniform(tls[i][j]-200,tls[i][j]+200)
            #print('butts')
            if tls[i][j] < lims[d[i]][0] or tls[i][j] > lims[d[i]][0]:
                tls[i][j] = random.uniform(tls[i][j]-200,tls[i][j]+200)
                print(f'd[i] = {d[i]} lims[d[i]] = {lims[d[i]]}, tls[i][j] = {tls[i][j]}')
                #print('farts')

    return tls

        
        #inc/dec until average of thing is 0.45 or 0.55 || 0.4 0.6
        #use list of lims for this

    print('hello!!')


'''
pass x and y of screen resoultion in pixels
sets the coordinates of what the x and y should be, and sets the list of 
bounds that the edges should be
returns the x and y coords as a list

This must also shrink anything as big, or bigger

If the resolution can fit inside of the window, let it
otherwise, create some scaling function

optional passing of the list of bounds. should call getlist if it is passed?

'''
def getxy(x=-1, y=-1):
    if x > win.width or y > win.height:
        x1 = (win.width//2)-(x/2) #left x
        x2 = (x/2)+win.width//2   #right x
        y1 = (y/2)+win.height//2    #top y
        y2 = (win.height//2)-(y/2)  #bottom y
        print('hello!')
    else:   
        x1 = (win.width//2)-(x/2) #left x
        x2 = (x/2)+win.width//2   #right x
        y1 = (y/2)+win.height//2    #top y
        y2 = (win.height//2)-(y/2)  #bottom y
    return [x1, y1, x2, y2]
       
'''
creates box justified to certain side of screen
pass x and y, and side of screen to justify to
returns list of box to draw to screen
'''

'''
x[0] x left
x[1] y top
x[2] x right
x[3] y bottom
'''

def xyjst(x, y, st):
    tls = [0,0,0,0]
    if st == 'br':
        tls[0] = win.width - x
        tls[1] = y
        tls[2] = win.width
        tls[3] = 0
    elif st == 'bl':
        print('poop')
    elif st == 'tr':
        print('poop')
    elif st == 'tl':
        print('poop')
    elif st == 'mr':
        print('poop')
    elif st == 'ml':
        print('poop')
    return tls

#create frame around box by whatever x is
#god enough

''' ?? not sure if this is right
x[0] x left
x[1] y top
x[2] x right
x[3] y bottom
'''
#everything here goes clockwise

def frmmkr(tls, x):
    #print('poop')
    #left
    lx1 = tls[0]-x
    ly1 = tls[1]+x
    lx2 = tls[0]
    ly2 = tls[3]-x
    #top
    tx1 = tls[0]-x
    ty1 = tls[1]+x
    tx2 = tls[2]+x
    ty2 = tls[1]
    #right
    rx1 = tls[2]
    ry1 = tls[1]+x
    rx2 = tls[2]+x
    ry2 = tls[3]-x
    #bottom
    bx1 = tls[0]-x
    by1 = tls[3]
    bx2 = tls[2]+x
    by2 = tls[3]-x

    return [lx1,ly1,lx2,ly2,tx1,ty1,tx2,ty2,rx1,ry1,rx2,ry2,bx1,by1,bx2,by2]

#this is retarded. I know theres something in pyglet that's just drawing an array of vectors.
#figure that out or not maybe. I bet it would speed up the program

def drwbx(tls):
    glVertex2f(tls[0],tls[1])       #top left
    glVertex2f(tls[2],tls[3])       #bottom right
    glVertex2f(tls[0],tls[3])      #bottom left
    glVertex2f(tls[0],tls[1])       #top left
    glVertex2f(tls[2],tls[3])      #bottom right
    glVertex2f(tls[2],tls[1])      #top right

def drwfrm(tls):
    #left
    glVertex2f(tls[0],tls[1])       #top left
    glVertex2f(tls[2],tls[3])       #bottom right
    glVertex2f(tls[0],tls[3])      #bottom left
    glVertex2f(tls[0],tls[1])       #top left
    glVertex2f(tls[2],tls[3])      #bottom right
    glVertex2f(tls[2],tls[1])      #top right
    #top
    glVertex2f(tls[0+4],tls[1+4])       #top left
    glVertex2f(tls[2+4],tls[3+4])       #bottom right
    glVertex2f(tls[0+4],tls[3+4])      #bottom left
    glVertex2f(tls[0+4],tls[1+4])       #top left
    glVertex2f(tls[2+4],tls[3+4])      #bottom right
    glVertex2f(tls[2+4],tls[1+4])      #top right
    #right
    glVertex2f(tls[0+8],tls[1+8])       #top left
    glVertex2f(tls[2+8],tls[3+8])       #bottom right
    glVertex2f(tls[0+8],tls[3+8])      #bottom left
    glVertex2f(tls[0+8],tls[1+8])       #top left
    glVertex2f(tls[2+8],tls[3+8])      #bottom right
    glVertex2f(tls[2+8],tls[1+8])      #top right
    #bottom
    glVertex2f(tls[0+12],tls[1+12])       #top left
    glVertex2f(tls[2+12],tls[3+12])       #bottom right
    glVertex2f(tls[0+12],tls[3+12])      #bottom left
    glVertex2f(tls[0+12],tls[1+12])       #top left
    glVertex2f(tls[2+12],tls[3+12])      #bottom right
    glVertex2f(tls[2+12],tls[1+12])      #top right

#APPEARENTLY some F*** that wrote python thought that it would be a good idea to make 
#the f****** EQUAL SIGN CREATE A POINTER BETWEEN LISTS
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
    global frame
    global scnl
    global lims
    if running == False:
        running = True
        wlol=copy.deepcopy(lol)     #who thought this was a good idea
        print('hello!')
        print(f'lol = {lol}\nwlol = {wlol}')
    #print(f'previous to increment\nlol = {lol[0][0]}\nwlol = {wlol[0][0]}\n\n{len(wlol)} {len(nlol)}')
    count+=1
    frame+=1
    if count == uplimf:
        lol = nlol
        nlol = randlist(lol, lims)
        #nlol = getlist(lims, t)
        wlol=copy.deepcopy(lol)     #monkeys with typewriters maybe
        #lol = getlist(t)
        count = 0
    inc()
    print(f'{x} seconds since last udate, {count/24} secs since switchup')#\ntwlol = {twlol}\ntnlol = {tnlol}')

@win.event
def on_draw():
    #scnlf = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
    #clear buffers
    glClear(GL_COLOR_BUFFER_BIT)
    glColor3f(0.241, 0.139, .61)
    #draw only the points
    #glBegin(GL_POINTS)`
    #draw outlines only
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    glBegin(GL_TRIANGLES)
    #glBegin(GL_QUADS)
    #glBegin(GL_QUAD_STRIP)
    #glBegin(GL_TRIANGLE_STRIP)

    print('lol = ', lol[0][0], '\nnlol = ', nlol[0][0], '\nwlol = ', wlol[0][0])
    for i in range(0,len(lol), 2):
        for j in range(0,t):
            #print('\r')
            glVertex2f(wlol[i][j],wlol[i+1][j])
    
    #just setup bounds first?
    #use percentages????????
    #from 
    glColor3f(1,1,1)
    #draw screen box

    if bx[2]:
        drwbx(scnl)
        scnlf = frmmkr(scnl, 5)
        drwfrm(scnlf)

    print(f'scnl[0] = {scnl[0]},scnl[1]  = {scnl[1]},scnl[2] = {scnl[2]},scnl[3] = {scnl[3]}')
    
    if fccm[2]:
        glVertex2f(fcl[0],fcl[1])       #bottom left
        glVertex2f(fcl[0],fcl[3])       #top left
        glVertex2f(fcl[2],fcl[1])      #bottom right
        glVertex2f(fcl[0],fcl[3])       #top left
        glVertex2f(fcl[2],fcl[1])      #bottom right
        glVertex2f(fcl[2],fcl[3])      #top right
    glEnd()
    #pyglet.image.get_buffer_manager().get_color_buffer().save('./scrnsht/'+str(frame).rjust(4,'0')+'.png')

scnl = getxy(bx[0], bx[1])
lims = getlims(scnl[0], scnl[1], scnl[2], scnl[3])
lol = getlist(lims,t)
fcl = xyjst(fccm[0], fccm[1],'br')
print(f'scnl = {scnl}, fcl = {fcl}')
nlol = randlist(lol, lims)
#nlol = getlist(lims, t)
udate(dt)
pyglet.clock.schedule_interval(udate, 1/fps)
pyglet.app.run()

while true: dt = clock.tick()
#not sure what to do here... ill implement later, just get the whole boarder thing working for now

def main():
    global D
    global dbx
    global fccm
    try:
        opts, args = getopt.getopt(sys.argv,"h:3d:43:169:fccm:")
    except getopt.GetoptError as err:
      print(str(err))

      print(f'\n-h shows this screen\n-3d enables 3d mode\n-43 enables the 4:3 aspect ratio\n-169 enables 16:9 ratio(default)\n-fccm enables facecam')
      sys.exit(2)
    for opt, arg in opts:
        if opt in "-3d": D = True
        elif opt in "fccm": fccm = True

    #while True:
        #dt = clock.tick()

if __name__ == "__main__":
    main()



