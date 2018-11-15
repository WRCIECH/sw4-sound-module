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
        #MESSAGE = pack('18d',
        MESSAGE = pack('5didididi6d',
        self.A_e,
        self.r_s,
        self.theta,
        self.phi,
        self.A_prim,
        self.B,
        self.d_prim,
        self.i,
        self.M_d,
        self.l,
        self.s_prim,
        self.V,
        self.m_prim,

        self.N_prim,
        self.delta_T,
        self.c_inf,
        self.Mach_inf,
        self.rho_inf
        )
        recvd = self.sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))
        #print("send udp (frequency, volume, gear_mix): ", self.frequency, self.volume, self.gear_mix)

    def set_A_e(self, val):
        self.A_e = float(val)
        self.send_udp()
    def set_r_s(self, val):
        self.r_s = float(val)
        self.send_udp()
    def set_theta(self, val):
        self.theta = float(val)
        self.send_udp()
    def set_phi(self, val):
        self.phi = float(val)
        self.send_udp()
    def set_A_prim(self, val):
        self.A_prim = float(val)
        self.send_udp()
    def set_B(self, val):
        self.B = float(val)
        self.send_udp()
    def set_d_prim(self, val):
        self.d_prim = float(val)
        self.send_udp()
    def set_i(self, val):
        self.i = float(val)
        self.send_udp()
    def set_M_d(self, val):
        self.M_d = float(val)
        self.send_udp()
    def set_l(self, val):
        self.l = float(val)
        self.send_udp()
    def set_s_prim(self, val):
        self.s_prim = float(val)
        self.send_udp()
    def set_V(self, val):
        self.V = float(val)
        self.send_udp()
    def set_m_prim(self, val):
        self.m_prim = float(val)
        self.send_udp()
    def set_Mach_inf(self, val):
        self.Mach_inf = float(val)
        self.send_udp()
    def set_N_prim(self, val):
        self.N_prim = float(val)
        self.send_udp()
    def set_delta_T(self, val):
        self.delta_T = float(val)
        self.send_udp()
    def set_c_inf(self, val):
        self.c_inf = float(val)
        self.send_udp()
    def set_rho_inf(self, val):
        self.rho_inf = float(val)
        self.send_udp()

    def createWidgets(self):
        Label(text="A_e").grid(row=0, column=0)
        w = Scale(self.master, from_=0.01, to=10.0, orient=HORIZONTAL, command=self.set_A_e, resolution=0.01)
        w.grid(row=0, column=1)
        w.set(0.7853981633)

        Label(text="r_s").grid(row=1, column=0)
        w = Scale(from_=0.01, to=10.0, orient=HORIZONTAL, command=self.set_r_s, resolution=0.01)
        w.grid(row=1, column=1)
        w.set(0.88622692540)

        Label(text="A_prim").grid(row=2, column=0)
        w = Scale(from_=0.1, to=10.0, orient=HORIZONTAL, command=self.set_A_prim, resolution=0.1)
        w.grid(row=2, column=1)
        w.set(1.0)

        Label(text="B").grid(row=3, column=0)
        w = Scale(from_=2, to=100, orient=HORIZONTAL, command=self.set_B, resolution=1.0)
        w.grid(row=3, column=1)
        w.set(20.0)

        Label(text="d_prim").grid(row=4, column=0)
        w = Scale(from_=0.3, to=4.0, orient=HORIZONTAL, command=self.set_d_prim, resolution=0.01)
        w.grid(row=4, column=1)
        w.set(1.128)

        Label(text="i").grid(row=5, column=0)
        w = Scale(from_=1, to=2, orient=HORIZONTAL, command=self.set_i, resolution=1.0)
        w.grid(row=5, column=1)
        w.set(1.0)

        Label(text="M_d").grid(row=6, column=0)
        w = Scale(from_=0.5, to=2.0, orient=HORIZONTAL, command=self.set_M_d, resolution=0.1)
        w.grid(row=6, column=1)
        w.set(1.0)

        Label(text="l").grid(row=7, column=0)
        w = Scale(from_=1, to=2, orient=HORIZONTAL, command=self.set_l, resolution=1.0)
        w.grid(row=7, column=1)
        w.set(1.0)

        Label(text="theta").grid(row=8, column=0)
        w = Scale(from_=1, to=2, orient=HORIZONTAL, command=self.set_theta, resolution=1.0)
        w.grid(row=8, column=1)
        w.set(1.0)

###########

        Label(text="s_prim").grid(row=0, column=2)
        w = Scale(from_=0.2, to=10.0, orient=HORIZONTAL, command=self.set_s_prim, resolution=0.1)
        w.grid(row=0, column=3)
        w.set(1.0)

        Label(text="V").grid(row=1, column=2)
        w = Scale(from_=10.0, to=200.0, orient=HORIZONTAL, command=self.set_V, resolution=1.0)
        w.grid(row=1, column=3)
        w.set(50.0)

        Label(text="m_prim").grid(row=2, column=2)
        w = Scale(from_=0, to=0.2, orient=HORIZONTAL, command=self.set_m_prim, resolution=0.01)
        w.grid(row=2, column=3)
        w.set(0.2)

        Label(text="Mach_inf").grid(row=3, column=2)
        w = Scale(from_=0, to=0.9, orient=HORIZONTAL, command=self.set_Mach_inf, resolution=0.1)
        w.grid(row=3, column=3)
        w.set(0.0)

        Label(text="N_prim").grid(row=4, column=2)
        w = Scale(from_=0, to=0.5, orient=HORIZONTAL, command=self.set_N_prim, resolution=0.01)
        w.grid(row=4, column=3)
        w.set(0.3)

        Label(text="delta T").grid(row=5, column=2)
        w = Scale(from_=0, to=1.3, orient=HORIZONTAL, command=self.set_delta_T, resolution=0.1)
        w.grid(row=5, column=3)
        w.set(0.2)

        Label(text="c_inf").grid(row=6, column=2)
        w = Scale(from_=200.0, to=400.0, orient=HORIZONTAL, command=self.set_c_inf, resolution=0.1)
        w.grid(row=6, column=3)
        w.set(340.294)

        Label(text="rho_inf").grid(row=7, column=2)
        w = Scale(from_=0.2, to=1.5, orient=HORIZONTAL, command=self.set_rho_inf, resolution=0.1)
        w.grid(row=7, column=3)
        w.set(1.225)

        Label(text="phi").grid(row=8, column=2)
        w = Scale(from_=1, to=2, orient=HORIZONTAL, command=self.set_phi, resolution=1.0)
        w.grid(row=8, column=3)
        w.set(1.0)


    def __init__(self, master=None):
        Frame.__init__(self, master)
        # self.pack()
        self.master.geometry("500x500")
        self.sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
        self.createWidgets()
        self.A_e=0
        self.r_s=0
        self.theta=0
        self.phi=0
        self.A_prim=0
        self.B=0
        self.d_prim=0
        self.i=0
        self.M_d=0
        self.l=0
        self.s_prim=0
        self.V=0
        self.m_prim=0
        self.Mach_inf=0
        self.N_prim=0
        self.delta_T=0
        self.c_inf=0
        self.rho_inf=0

root = Tk()
root.title('Engine compressor noise')
app = Application(master=root)
app.mainloop()
root.destroy()
