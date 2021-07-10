import socket

SERVER_IP = "127.0.0.1"  # Servers run on local machine
SERVER_PORT = 3000


def connect():
    """
    Connects a socket to the server ip and port
    :return: the socket
    """
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((SERVER_IP, SERVER_PORT))
    return s


def error_and_exit(error_msg):
    """
    In case of an error, it displays the error message and exits
    :param error_msg: the error message to display
    :return: Nothing
    """
    print(error_msg)
    exit()


def close_socket(s):
    """
    Closes the given socket.
    :param s: the socket
    :return: Nothing
    """
    s.close()


def send_data(s, data):
    """
    Sends given data to the socket.
    :param s: the socket
    :param data: the data given
    :return: Nothing
    """
    s.send(data.encode())


def recv_data(s):
    """
    Recieves data from socket.
    :param s: the socket we recieve from.
    :return: data recieved.
    """
    data = s.recv(1024).decode()
    return data
