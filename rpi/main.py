from rpi.VelocityControl import PID
from rpi.communicator import Communicator

com = Communicator("communicator")
vel_ctrl = PID("pid", com)
vel_ctrl.start()

vel_ctrl.update_vel_left(200)
vel_ctrl.update_vel_right(200)

