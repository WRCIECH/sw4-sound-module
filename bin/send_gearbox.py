try:
    # for Python2
    from Tkinter import *   ## notice capitalized T in Tkinter 
except ImportError:
    # for Python3
    from tkinter import *   ## notice lowercase 't' in tkinter here
from struct import *
import socket

UDP_IP = "127.0.0.1"
UDP_PORT = 7160

class Application(Frame):
    def send_udp(self):
        MESSAGE = pack('fff', self.engine_speed, self.gear_ratio, self.gear_mix)
        recvd = self.sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
        print("send udp (engine_speed, gear_ratio, gear_mix): ", self.engine_speed, self.gear_ratio, self.gear_mix)

    def set_engine_speed(self, val):
        self.engine_speed = float(val)
        self.send_udp()

    def set_gear_ratio(self, val):
        self.gear_ratio = float(val)
        self.send_udp()

    def set_gear_mix(self, val):
        self.gear_mix = float(val)
        self.send_udp()

    def createWidgets(self):
        Scale(from_=0, to=100, orient=HORIZONTAL, command=self.set_engine_speed, resolution=0.01).grid(row=0, column=0)
        Label(text="Engine speed").grid(row=1, column=0)

        Scale(from_=0, to=14.0, orient=HORIZONTAL, command=self.set_gear_ratio, resolution=0.01).grid(row=2, column=0)
        Label(text="gear_ratio").grid(row=3, column=0)

        Scale(from_=0, to=1, orient=HORIZONTAL, command=self.set_gear_mix, resolution=0.01).grid(row=0, column=1)
        Label(text="gear_mix").grid(row=1, column=1)


    def __init__(self, master=None):
        Frame.__init__(self, master)
        # self.pack()
        self.master.geometry("500x500")
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        self.createWidgets()
        self.engine_speed = 0.0
        self.gear_ratio = 0.0
        self.gear_mix = 0.0

root = Tk()
root.title('Gearbox noise')
app = Application(master=root)
app.mainloop()
root.destroy()
