import serial
import RPi.GPIO as GPIO
import time

ser = serial.Serial("dev/ttyACM0", 9600)
ser.baudrate = 9600

GPIO.setmode(GPIO.BOARD)
while True:
    print(ser.readline())