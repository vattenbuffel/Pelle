import serial
import RPi.GPIO as GPIO
import threading
import time
import queue


class communicator:
    def __init__(self, name):
        GPIO.setmode(GPIO.BOARD)
        self.ser = serial.Serial(port="/dev/ttyUSB0",
                                 baudrate=115200,
                                 parity=serial.PARITY_NONE,
                                 stopbits=serial.STOPBITS_ONE,
                                 bytesize=serial.EIGHTBITS,
                                 timeout=1)
        time.sleep(1)
        print('ser opened')
        self.name = name
        self.ser_lock = threading.Lock()
        self.data_to_send = queue.Queue(1)
        self.received_data = queue.Queue(1)
        self.data_sent = threading.Event()
        self.data = ""

        data_sender = DataSender("data_sender", self.data_to_send, self.ser, self.data_sent, self.ser_lock)
        data_reader = DataReader("data_reader", self.received_data, self.ser, self.data_sent, self.ser_lock)
        data_sender.start()
        data_reader.start()

    def send_request(self, data):
        self.data_to_send.put(data)

    def get_data(self):
        return self.received_data.get()


class DataSender(threading.Thread):
    def __init__(self, name, data_to_send, ser, data_sent, ser_lock):
        threading.Thread.__init__(self)
        self.name = name
        self.data_to_send = data_to_send
        self.ser = ser
        self.data_sent = data_sent
        self.ser_lock = ser_lock

    def run(self):
        while True:
            data_to_send = self.data_to_send.get()
            self.ser_lock.acquire()
            print(self.name, 'sends', data_to_send.encode())
            self.ser.write(data_to_send.encode())
            self.data_sent.set()
            self.ser_lock.release()


class DataReader(threading.Thread):
    def __init__(self, name, received_data, ser, data_sent, ser_lock):
        threading.Thread.__init__(self)
        self.name = name
        self.received_data = received_data
        self.ser = ser
        self.data_sent = data_sent
        self.ser_lock = ser_lock

    def run(self):
        while True:
            self.data_sent.wait()
            self.data_sent.clear()

            read = b''
            self.ser_lock.acquire()
            while self.ser.in_waiting == 0:
                pass

            while self.ser.in_waiting > 0:
                data = self.ser.read(1)
                print(self.name, 'received', data)
                if data == b'\r':
                    self.received_data.put(read.decode("utf-8"))
                    self.ser.flushInput()
                    read = b''

                read += data
            self.ser_lock.release()


t1 = communicator("t1")

t1.send_request("3.4.5")
print(t1.get_data())