import time
import threading
from rpi import communicator
import math
import matplotlib.pyplot as plt
import random


class PID(threading.Thread):
    def __init__(self, name, communication):
        threading.Thread.__init__(self)
        self.name = name
        self.communicator = communication
        self.vel_left = 0
        self.vel_right = 0

        self.vs_left = []
        self.vs_right = []
        self.ref_vs_left = []
        self.ref_vs_right = []
        self.ts = []
        self.time_init = 0

        self.kp = 0.5
        self.ki = 0.4
        self.kd = 0.0
        self.radius = 0.025
        self.segments = 2096
        self.v_max = 207  # mm/s
        self.v_min = 40  # mm/s

    def update_vel_left(self, vel):
        self.vel_left = vel

    def update_vel_right(self, vel):
        self.vel_right = vel

    def get_left_segments(self):
        self.communicator.send_request('report_left')
        return self.communicator.get_data()

    def get_right_segments(self):
        self.communicator.send_request('report_right')
        return self.communicator.get_data()

    def limit_vel(self, vel):
        # make sure vel isn't too big, can't be bigger than 10000 for some reason
        if vel > 10000:
            return 10000
        elif vel < -10000:
            return -10000
        return vel

    def actuate_vel_left(self, vel):
        vel = self.limit_vel(vel)
        self.communicator.send_request("left_vel:" + str(vel))
        self.communicator.get_data()

    def actuate_vel_right(self, vel):
        vel = self.limit_vel(vel)
        self.communicator.send_request("right_vel:" + str(vel))
        self.communicator.get_data()

    def plotter(self, t, v_left, v_right):
        if self.time_init == 0:
            self.time_init = time.time()

        self.ts.append(int((t - self.time_init) * 1000))
        self.vs_right.append(v_right)
        self.vs_left.append(v_left)
        self.ref_vs_right.append(self.vel_right)
        self.ref_vs_left.append(self.vel_left)

        if self.vel_right == -1:
            self.actuate_vel_right(0)
            self.actuate_vel_left(0)
            plt.plot(self.ts, self.vs_left, label='left')
            plt.plot(self.ts, self.vs_right, label='right')
            plt.plot(self.ts, self.ref_vs_left, label='left ref')
            plt.plot(self.ts, self.ref_vs_right, label='right ref')
            plt.title('kp = ' + str(self.kp) + '\nki = ' + str(self.ki) + '\nkd = ' + str(self.kd))
            plt.legend()
            plt.show()

            exit()

    def run(self):
        t_old_left = time.time()
        t_old_right = time.time()
        e_old_left = 0
        e_old_right = 0
        I_left = 0
        I_right = 0

        while True:
            segments_passed = int(self.get_left_segments())
            t_cur = time.time()
            dt = (t_cur - t_old_left)

            cur_vel_left = (segments_passed / self.segments * math.pi * 2 * self.radius) / dt * 1000
            e_cur_left = self.vel_left - cur_vel_left

            P = e_cur_left * self.kp
            I_left += e_cur_left * self.ki
            D = (e_cur_left - e_old_left) / (t_cur - t_old_left) * self.kd

            PID_left = P + I_left + D
            self.actuate_vel_left(int(PID_left))
            t_old_left = time.time()
            e_old_left = e_cur_left

            segments_passed = int(self.get_right_segments())
            t_cur = time.time()
            dt = (t_cur - t_old_right)

            cur_vel_right = (segments_passed / self.segments * math.pi * 2 * self.radius) / dt * 1000
            e_cur_right = self.vel_right - cur_vel_right

            P = e_cur_right * self.kp
            I_right += e_cur_right * self.ki
            D = (e_cur_right - e_old_right) / (t_cur - t_old_right) * self.kd

            PID_right = P + I_right + D
            self.actuate_vel_right(int(PID_right))
            t_old_right = time.time()
            e_old_right = e_cur_right

            self.plotter(t_cur, cur_vel_left, cur_vel_right)

            # time.sleep(0.001)



