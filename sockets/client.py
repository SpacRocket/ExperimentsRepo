import socket
import sys
import select
import errno

HEADER_LENGTH = 10

IP = "127.0.0.1"
PORT = 1234

ENCODE = "utf-8"

my_username = input("Username: ")
username = my_username
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((IP, PORT))
client_socket.setblocking(False)

'''@param msg is in string format'''
def create_a_packet(msg):
    msg = msg.encode(ENCODE)
    header_msg = f"{len(msg):<{HEADER_LENGTH}}".encode(ENCODE)
    return header_msg + msg

#Send login message
client_socket.send(create_a_packet(username))

while True:
    message = input(f"{my_username} > ")
    if message:
        client_socket.send(create_a_packet(message))

    try:
        while True:
            username_header = client_socket.recv(HEADER_LENGTH)
            if not len(username_header):
                print("Connection closed by the server")
                sys.exit()

            username_length = int(username_header.decode("utf-8").strip())
            username = client_socket.recv(username_length).decode("utf-8")

            message_header = client_socket.recv(HEADER_LENGTH)
            message_length = int(message_header.decode("utf-8").strip())
            message = client_socket.recv(message_length).decode("utf-8")

            print(f"{username} > {message}")

    except IOError as e:
        if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
            print('Error while reading', str(e))
            sys.exit()
        continue

    except Exception as e:
        print('General error', str(e))
        sys.exit()
        pass
