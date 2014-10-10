#!/usr/bin/python2.7
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

def getLineCoord(x_offset,y_offset):
    return 430+x_offset,200+y_offset

def getNumCoord(x_offset,y_offset):
    return 428+x_offset,200+y_offset

class Example(Frame):
  
    def __init__(self, parent):
        Frame.__init__(self, parent)   
         
        self.parent = parent        
        self.canvas = Canvas(self, bg = "gray")
        self.initUI()
        
    def initUI(self):
      
        self.parent.title("Networking Tree")        
        self.pack(fill=BOTH, expand=1)
        # Init the coordinates
        self.coordinates=[(0,0), (125,-125), (170,0), (170,150), (0,150), (-175,50), (-350,100), (-350,200), (-150, -100), (-350, -100)]
        
        self.drawBase()
        
        # Setup the socket
        # Read the first values
        # Request the next values

        # Draw text 
        for i in range(0,10):
            self.canvas.create_text(*getNumCoord(*self.coordinates[i]), anchor=W, font="Purisa",
            text="1")

        b = Button(self.canvas, text="Step", width=30, command=self.update)
        b.pack(side=BOTTOM)

        

        self.canvas.pack(fill=BOTH, expand=1)

    def update(self):
        self.parent.title("Networking Tree")        
        self.pack(fill=BOTH, expand=1)
        
        self.canvas.delete("all") # Redraw the canvas
        
        self.drawBase()

        # Draw text 
        for i in range(0,10):
            self.canvas.create_text(*getNumCoord(*self.coordinates[i]), anchor=W, font="Purisa",
            text="2")

        self.canvas.pack(fill=BOTH, expand=1)


    def drawBase(self):
        # Draw the connections
        self.canvas.create_line(getLineCoord(*self.coordinates[0]), getLineCoord(*self.coordinates[1]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[0]), getLineCoord(*self.coordinates[2]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[0]), getLineCoord(*self.coordinates[4]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[0]), getLineCoord(*self.coordinates[5]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[0]), getLineCoord(*self.coordinates[8]), fill="white", width=2.0)

        self.canvas.create_line(getLineCoord(*self.coordinates[1]), getLineCoord(*self.coordinates[0]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[1]), getLineCoord(*self.coordinates[2]), fill="white", width=2.0)

        self.canvas.create_line(getLineCoord(*self.coordinates[3]), getLineCoord(*self.coordinates[2]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[3]), getLineCoord(*self.coordinates[4]), fill="white", width=2.0)

        self.canvas.create_line(getLineCoord(*self.coordinates[5]), getLineCoord(*self.coordinates[6]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[5]), getLineCoord(*self.coordinates[4]), fill="white", width=2.0)
        self.canvas.create_line(getLineCoord(*self.coordinates[3]), getLineCoord(*self.coordinates[4]), fill="white", width=2.0)

        self.canvas.create_line(getLineCoord(*self.coordinates[6]), getLineCoord(*self.coordinates[7]), fill="white", width=2.0)

        self.canvas.create_line(getLineCoord(*self.coordinates[8]), getLineCoord(*self.coordinates[9]), fill="white", width=2.0)

        # Draw the circles
        for i in self.coordinates:
            self.canvas.create_oval(getCoord(*i), fill="white", outline="white")

def main():
    # start Main application
    root = Tk()
    ex = Example(root)
    root.geometry("820x450+300+300")
    root.mainloop()  

if __name__ == '__main__':
    main()  
