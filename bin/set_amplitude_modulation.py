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
        MESSAGE = pack('ffff', self.A0, self.A1, self.f0, self.f1)
        recvd = self.sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
        print("send udp (A0, A1, f0, f1): ", self.A0, self.A1, self.f0, self.f1)

    def set_A0(self, val):
        self.A0 = float(val)
        self.send_udp()

    def set_A1(self, val):
        self.A1 = float(val)
        self.send_udp()

    def set_f0(self, val):
        self.f0 = float(val)
        self.send_udp()

    def set_f1(self, val):
        self.f1 = float(val)
        self.send_udp()

    def createWidgets(self):
        Scale(from_=0, to=1.0, orient=HORIZONTAL, command=self.set_A0, resolution=0.01).grid(row=0, column=0)
        Label(text="A0 amplitude").grid(row=1, column=0)

        Scale(from_=0, to=1.0, orient=HORIZONTAL, command=self.set_A1, resolution=0.01).grid(row=2, column=0)
        Label(text="A1 amplitude").grid(row=3, column=0)

        Scale(from_=0, to=22000, orient=HORIZONTAL, command=self.set_f0, resolution=1.0).grid(row=0, column=1)
        Label(text="f0 frequency").grid(row=1, column=1)

        Scale(from_=0, to=22000, orient=HORIZONTAL, command=self.set_f1, resolution=1.0).grid(row=2, column=1)
        Label(text="f1 frequency").grid(row=3, column=1)


    def __init__(self, master=None):
        Frame.__init__(self, master)
        # self.pack()
        self.master.geometry("500x500")
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        self.createWidgets()
        self.A0 = 0.0
        self.A1 = 0.0
        self.f0 = 0.0
        self.f1 = 0.0

root = Tk()
app = Application(master=root)
app.mainloop()
root.destroy()
