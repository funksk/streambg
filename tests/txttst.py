import pyglet
from pyglet.gl import *

window = pyglet.window.Window(vsync=False)

label = pyglet.text.Label('Hello, world',
                          font_name='Times New Roman',
                          font_size=36,
                          x=window.width//2, y=window.height//2,
                          anchor_x='center', anchor_y='center')

@window.event
def on_draw():
	window.clear()
	glClear(GL_COLOR_BUFFER_BIT)
	label.draw()
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE)
	glBegin(GL_TRIANGLES)
	glVertex2f(126,200)
	glVertex2f(50,300)
	glVertex2f(150,100)
	glEnd()


pyglet.app.run()