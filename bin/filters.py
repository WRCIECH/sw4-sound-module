try:
    # for Python2
    from Tkinter import *   ## notice capitalized T in Tkinter 
except ImportError:
    # for Python3
    from tkinter import *   ## notice lowercase 't' in tkinter here
from struct import *
import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 7150

class Application(Frame):
    def send_udp(self):
        MESSAGE = pack('f', self.low_pass_cutoff_frequency)
        recvd = self.sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
        print("send udp: ", self.low_pass_cutoff_frequency)

    def set_param(self, val):
        self.low_pass_cutoff_frequency = float(val)
        self.send_udp()

    def createWidgets(self):
        Scale(from_=0, to=22000, orient=HORIZONTAL, command=self.set_param, resolution=1.0).grid(row=0, column=0)
        Label(text="Low Pass cutoff frequency").grid(row=1, column=0)


    def __init__(self, master=None):
        Frame.__init__(self, master)
        # self.pack()
        self.master.geometry("500x500")
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        self.createWidgets()
        self.low_pass_cutoff_frequency = 0.0

root = Tk()
app = Application(master=root)
app.mainloop()
root.destroy()
