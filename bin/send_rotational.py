try:
    # for Python2
    from Tkinter import *   ## notice capitalized T in Tkinter 
except ImportError:
    # for Python3
    from tkinter import *   ## notice lowercase 't' in tkinter here
from struct import *
import socket
import math

UDP_IP = "127.0.0.1"
UDP_PORT = 7155

class Application(Frame):
    def send_udp(self):
        MESSAGE = pack('16d3i',
        self.Omega,
        self.B,
        self.c,
        self.rho,
        self.V,
        self.R,
        self.X,
        self.Y,
        self.R_begin,
        self.R_end,
        self.chord,
        self.collective,
        self.cyclic,
        self.tilt,
        self.Vc,
        self.vflap,
        self.r_size,
        self.psi_size,
        self.max_harmonic_number
        )
        recvd = self.sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
        #print("send udp (frequency, volume, gear_mix): ", self.frequency, self.volume, self.gear_mix)

    def set_Omega(self, val):
        self.Omega = float(val)/60.0*2.0*math.pi
        self.send_udp()
    def set_B(self, val):
        self.B = float(val)
        self.send_udp()
    def set_c(self, val):
        self.c = float(val)
        self.send_udp()
    def set_rho(self, val):
        self.rho = float(val)
        self.send_udp()
    def set_V(self, val):
        self.V = float(val)
        self.send_udp()
    def set_R(self, val):
        self.R = float(val)
        self.send_udp()
    def set_X(self, val):
        self.X = float(val)
        self.send_udp()
    def set_Y(self, val):
        self.Y = float(val)
        self.send_udp()
    def set_R_begin(self, val):
        self.R_begin = float(val)
        self.send_udp()
    def set_R_end(self, val):
        self.R_end = float(val)
        self.send_udp()

    def set_chord(self, val):
        self.chord = float(val)
        self.send_udp()
    def set_collective(self, val):
        self.collective = float(val)/180.0*math.pi
        self.send_udp()
    def set_cyclic(self, val):
        self.cyclic = float(val)/180.0*math.pi
        self.send_udp()
    def set_tilt(self, val):
        self.tilt = float(val)/180.0*math.pi
        self.send_udp()
    def set_Vc(self, val):
        self.Vc = float(val)
        self.send_udp()
    def set_vflap(self, val):
        self.vflap = float(val)
        self.send_udp()
    def set_r_size(self, val):
        self.r_size = float(val)
        self.send_udp()
    def set_psi_size(self, val):
        self.psi_size = float(val)
        self.send_udp()
    def set_max_harmonic_number(self, val):
        self.max_harmonic_number = float(val)
        self.send_udp()

    def createWidgets(self):
        Label(text="RPM").grid(row=0, column=0)
        w = Scale(self.master, from_=100.0, to=600.0, orient=HORIZONTAL, command=self.set_Omega, resolution=0.1)
        w.grid(row=0, column=1)
        w.set(400)

        Label(text="B").grid(row=1, column=0)
        w = Scale(from_=1, to=10, orient=HORIZONTAL, command=self.set_B, resolution=1.0)
        w.grid(row=1, column=1)
        w.set(3)

        Label(text="c").grid(row=2, column=0)
        w = Scale(from_=200.0, to=400.0, orient=HORIZONTAL, command=self.set_c, resolution=0.1)
        w.grid(row=2, column=1)
        w.set(340.294)

        Label(text="rho").grid(row=3, column=0)
        w = Scale(from_=0.2, to=1.5, orient=HORIZONTAL, command=self.set_rho, resolution=0.1)
        w.grid(row=3, column=1)
        w.set(1.225)

        Label(text="V").grid(row=4, column=0)
        w = Scale(from_=0.0, to=300.0, orient=HORIZONTAL, command=self.set_V, resolution=0.1)
        w.grid(row=4, column=1)
        w.set(0.0)

        Label(text="R").grid(row=5, column=0)
        w = Scale(from_=1.0, to=10.0, orient=HORIZONTAL, command=self.set_R, resolution=0.1)
        w.grid(row=5, column=1)
        w.set(5.0)

        Label(text="X").grid(row=6, column=0)
        w = Scale(from_=-500.0, to=500.0, orient=HORIZONTAL, command=self.set_X, resolution=1.0)
        w.grid(row=6, column=1)
        w.set(-100.0)

        Label(text="Y").grid(row=7, column=0)
        w = Scale(from_=0.0, to=100.0, orient=HORIZONTAL, command=self.set_Y, resolution=0.1)
        w.grid(row=7, column=1)
        w.set(1.0)

        Label(text="R begin").grid(row=8, column=0)
        w = Scale(from_=0.01, to=0.5, orient=HORIZONTAL, command=self.set_R_begin, resolution=0.01)
        w.grid(row=8, column=1)
        w.set(0.2)

        Label(text="R end").grid(row=9, column=0)
        w = Scale(from_=0.70, to=1.0, orient=HORIZONTAL, command=self.set_R_end, resolution=0.01)
        w.grid(row=9, column=1)
        w.set(0.95)

###########

        Label(text="chord").grid(row=0, column=2)
        w = Scale(from_=0.01, to=0.3, orient=HORIZONTAL, command=self.set_chord, resolution=0.01)
        w.grid(row=0, column=3)
        w.set(0.1)

        Label(text="collective").grid(row=1, column=2)
        w = Scale(from_=8.0, to=70.0, orient=HORIZONTAL, command=self.set_collective, resolution=1.0)
        w.grid(row=1, column=3)
        w.set(0.0)

        Label(text="cyclic").grid(row=2, column=2)
        w = Scale(from_=0, to= 70.0, orient=HORIZONTAL, command=self.set_cyclic, resolution=1.0)
        w.grid(row=2, column=3)
        w.set(0.0)

        Label(text="tilt").grid(row=3, column=2)
        w = Scale(from_=0, to=70.0, orient=HORIZONTAL, command=self.set_tilt, resolution=1.0)
        w.grid(row=3, column=3)
        w.set(0.0)

        Label(text="Vc").grid(row=4, column=2)
        w = Scale(from_=0, to=10.0, orient=HORIZONTAL, command=self.set_Vc, resolution=0.1)
        w.grid(row=4, column=3)
        w.set(0.0)

        Label(text="vflap").grid(row=5, column=2)
        w = Scale(from_=0, to=20.0, orient=HORIZONTAL, command=self.set_vflap, resolution=0.1)
        w.grid(row=5, column=3)
        w.set(0.0)

        Label(text="r size").grid(row=6, column=2)
        w = Scale(from_=5.0, to=50.0, orient=HORIZONTAL, command=self.set_r_size, resolution=1.0)
        w.grid(row=6, column=3)
        w.set(16)

        Label(text="psi size").grid(row=7, column=2)
        w = Scale(from_=5.0, to=50.0, orient=HORIZONTAL, command=self.set_psi_size, resolution=1.0)
        w.grid(row=7, column=3)
        w.set(16.0)

        Label(text="max harmonic number").grid(row=8, column=2)
        w = Scale(from_=1, to=100, orient=HORIZONTAL, command=self.set_max_harmonic_number, resolution=1.0)
        w.grid(row=8, column=3)
        w.set(60.0)


    def __init__(self, master=None):
        Frame.__init__(self, master)
        # self.pack()
        self.master.geometry("500x500")
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        self.createWidgets()
        self.Omega=0
        self.B=0
        self.c=0
        self.rho=0
        self.V=0
        self.R=0
        self.X=0
        self.Y=0
        self.R_begin=0
        self.R_end=0
        self.chord=0
        self.collective=0
        self.cyclic=0
        self.tilt=0
        self.Vc=0
        self.vflap=0
        self.r_size=0
        self.psi_size=0
        self.max_harmonic_number=0

root = Tk()
root.title('Loading rotational noise')
app = Application(master=root)
app.mainloop()
root.destroy()
