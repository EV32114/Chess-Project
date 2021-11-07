import serial


def connect_to_port():
    port = serial.Serial('COM3', 9600)  # Baud rate is 9600
    return port


def get_input(port):
    return port.readline().decode()


def check_button_mode(data):
    if data == 'H\r\n':
        return True
    return False


def serial_write(port, data):
    port.write(data.encode())