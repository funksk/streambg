import pyglet
from pyglet.gl import *

win = pyglet.window.Window(1280, 720, resizable=True)

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
    glVertex2i(50, 50)
    glVertex2i(75,100)
    glVertex2i(200,200)
    glVertex2i(50,250)


    glEnd()

pyglet.app.run()
