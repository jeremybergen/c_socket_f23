import socket
import errno
import sys

def main():
    port = 1235
    host = "127.0.0.1"
    headerlength = 10

    username = input("What is your username? ")
    usernamelength = len(username)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        
        s.connect((host, port))
        s.setblocking(False)

        # s.sendall(username.encode())
        s.sendall(f"{usernamelength:<{headerlength}}{username}".encode())
        # 7         jbergen
        while True:
            message = input("Message to send: ")

            if message:
                print(f"Sending: {message}")
                s.send(message.encode())
            try:
                while True:
                    #receive messages
                    recvMessage = s.recv(1024).decode()
                    print(f"Received: {recvMessage}")
                    continue
            
            except IOError as e:
                if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
                    print(f"Reading error: {str(e)}")
                    sys.exit()
                continue
            # message = "Hello"
            # s.send(message.encode())
            # break


if __name__ == "__main__":
    main()