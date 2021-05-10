import pyglet
import decimal
import math
from pyglet.gl import *

win = pyglet.window.Window(1280, 720, resizable=True)
x = y = z = 0.0

def float_range(start, stop, step):
  while start < stop:
    yield float(start)
    start += decimal.Decimal(step)

@win.event
def on_resize(width, height):
    print(f'{width},{height}')
def on_draw():

    #clear buffers
    glClear(GL_COLOR_BUFFER_BIT)


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)

    glBegin(GL_LINE_STRIP)
    z = -50.0
    for i in float_range(0,3,0.1):
        x = 50.0*math.sin(i)
        y = 50.0*math.cos(i)

        glVertex3f(x,y,z)
        z+=0.5
    glEnd()

pyglet.app.run()
