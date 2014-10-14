#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

from Tkinter import *
import socket, os

def getCoord(x_offset,y_offset):
    return 400+x_offset,170+y_offset,460+x_offset,230+y_offset

def getLineCoord(x_offset,y_offset):
    return 430+x_offset,200+y_offset

def getNumCoord(x_offset,y_offset):
    return 420+x_offset,200+y_offset

    
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
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect(('localhost', 5789))

        # Read the first values
        data = self.getData()        

        # Draw text 
        for i in range(0,10):
            self.canvas.create_text(*getNumCoord(*self.coordinates[i]), anchor=W, font="Arial",
                                    text=data[i])

        newCan = Canvas(self.canvas, bg = "gray")
        newCan.pack(side=BOTTOM)

        b = Button(newCan, text="Step (Cycle)", command=self.step)
        b.pack(side=RIGHT)

        c = Button(newCan, text="Randomize", command=self.randomize)
        c.pack(side=RIGHT)

        d = Button(newCan, text="Inject Fault", command=self.fault)
        d.pack(side=RIGHT)        

        self.canvas.pack(fill=BOTH, expand=1)

    def step(self):
        self.client_socket.send("dummy")
        self.update()
    
    def update(self):
        self.parent.title("Networking Tree")        
        self.pack(fill=BOTH, expand=1)
        
        self.canvas.delete("all") # Redraw the canvas
        
        self.drawBase()
        data = self.getData()

        # Draw text 
        for i in range(0,10):
            self.canvas.create_text(*getNumCoord(*self.coordinates[i]), anchor=W, font="Arial",
                                    text=data[i])

        self.canvas.pack(fill=BOTH, expand=1)

    def randomize(self):
        self.client_socket.send("randomize")
        self.update()

    def fault(self):
        self.client_socket.send("fault")
        self.update()

    def getData(self):
        raw_data = self.client_socket.recv(1024)
        data  = raw_data.split(",")
        data = filter(None, data)
        return data


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
    os.system("./leaderElectionGeneral.out &")
    root = Tk()
    ex = Example(root)
    root.geometry("820x450+300+300")
    root.mainloop()
    ex.client_socket.close()

if __name__ == '__main__':
    main()  
