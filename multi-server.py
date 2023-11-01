import socket
import select


def main():
    port = 1234
    host = ""

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.bind((host, port))
        s.listen(5)

        connectedSockets = [s]
        clientList = {}

        print(f"Listening for client connections")

        while True:
            readSockets, _, exceptionSockets = select.select(connectedSockets, [], connectedSockets)

            for notifiedSocket in readSockets:
                if notifiedSocket == s:
                    clientSocket, clientAddress = s.accept()
                    connectedSockets.append(clientSocket)
                    clientList[clientSocket] = "jbergen"

                    print(f"Accepted new connection from: {clientAddress}")
                    # print(f"Current connections: {connectedSockets}")
                else:
                    try:
                        message = notifiedSocket.recv(1024).decode()
                        if len(message) == 0:
                            continue
                        print(f"Received from {notifiedSocket}: {message}")
                    except:
                        break
            


if __name__ == "__main__":
    main()