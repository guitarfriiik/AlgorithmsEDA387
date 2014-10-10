#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
ZetCode Tkinter tutorial

In this script, we draw text
on the window.

author: Jan Bodar
last modified: December 2010
website: www.zetcode.com
"""

from Tkinter import *

def getCoord(x_offset,y_offset):
    return 400+x_offset,170+y_offset,460+x_offset,230+y_offset

class Example(Frame):
  
    def __init__(self, parent):
        Frame.__init__(self, parent)   
         
        self.parent = parent        
        self.canvas = Canvas(self, bg = "gray")
        self.initUI()
        
    def initUI(self):
      
        self.parent.title("Networking Tree")        
        self.pack(fill=BOTH, expand=1)
        self.coordinates=[(0,0), (125,-125), (170,0), (170,150), (0,150), (-175,50), (-350,100), (-350,200), (-150, -100), (-350, -100)]

        
        # Replace by a loop using the coordinates
        self.canvas.create_oval(getCoord(0,0), fill="white", outline="white")
        self.canvas.create_oval(getCoord(125,-125), fill="white", outline="white")
        self.canvas.create_oval(getCoord(170,0), fill="white", outline="white")
        self.canvas.create_oval(getCoord(170,150), fill="white", outline="white")
        self.canvas.create_oval(getCoord(0,150), fill="white", outline="white")
        self.canvas.create_oval(getCoord(-175,50), fill="white", outline="white")
        self.canvas.create_oval(getCoord(-350,100), fill="white", outline="white")
        self.canvas.create_oval(getCoord(-350,200), fill="white", outline="white")
        self.canvas.create_oval(getCoord(-150,-100), fill="white", outline="white")
        self.canvas.create_oval(getCoord(-350,-100), fill="white", outline="white")

        #Attatch the routing and the numbers

        b = Button(self.canvas, text="Step", width=30, command=self.update)
        b.pack(side=BOTTOM)

        

        self.canvas.pack(fill=BOTH, expand=1)

    def update(self):
        self.parent.title("Networking Tree 2")        
        self.pack(fill=BOTH, expand=1)
        
        self.canvas.delete("all") # Redraw the canvas

        self.canvas.create_text(20, 30, anchor=W, font="Purisa",
            text="Most relationships seem so transitory PUSSY")
        self.canvas.create_text(20, 60, anchor=W, font="Purisa",
            text="They're good but not the permanent one")
        self.canvas.create_text(20, 130, anchor=W, font="Purisa",
            text="Who doesn't long for someone to hold")
        self.canvas.create_text(20, 160, anchor=W, font="Purisa",
            text="Who knows how to love without being told")                   
        self.canvas.create_text(20, 190, anchor=W, font="Purisa",
            text="Somebody tell me why I'm on my own")            
        self.canvas.create_text(20, 220, anchor=W, font="Purisa",
            text="If there's a soulmate for everyone")
        
        self.canvas.create_oval(100,100,200,200, fill="red", outline="red")

        self.canvas.pack(fill=BOTH, expand=1)


def main():
    root = Tk()
    ex = Example(root)
    root.geometry("820x450+300+300")
    root.mainloop()  

if __name__ == '__main__':
    main()  
