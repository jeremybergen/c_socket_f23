import socket
import select

def main():
    host = "127.0.0.1"
    port = 1235
    headerLength = 10

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as serverSocket:
        serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        serverSocket.bind((host, port))
        # serverSocket.listen()

        socketList = [serverSocket]
        clients = {}

        while True:
            readSockets, writeSockets, errorSockets = select.select(socketList, [], socketList)
            for notifiedSocket in readSockets:
                print(f"notifiedSocket: {notifiedSocket}")
                if notifiedSocket == serverSocket:
                    # clientSocket, clientAddress = notifiedSocket.accept()
                    # userName = "jbergen" + str(len(socketList))
                    header = notifiedSocket.recv(1024).decode()
                    messageLength = int(header[:10])
                    # userName = notifiedSocket.recv(messageLength).decode()
                    userName = header[10:]
                    clients[notifiedSocket] = userName
                    print(f"New client connected: {userName}")
                    socketList.append(notifiedSocket)
                    # new connection
                else:
                    userName = clients[notifiedSocket]
                    header = notifiedSocket.recv(headerLength).decode()
                    messageLength = int(header)
                    recvMessage = notifiedSocket.recv(messageLength).decode()
                    print(f"Received from {userName}: {recvMessage}")
                    for clientSocket in clients:
                        if clientSocket != notifiedSocket:
                            clientSocket.sendall(f"{len(userName):<{headerLength}}{userName}".encode())
                            clientSocket.sendall(f"{len(recvMessage):<{headerLength}}{recvMessage}".encode())
                    # existing connection


if __name__ == "__main__":
    main()








# import socket
# import select


# def main():
#     port = 1234
#     host = ""

#     with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#         s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
#         s.bind((host, port))
#         s.listen(5)

#         connectedSockets = [s]
#         clientList = {}

#         print(f"Listening for client connections")

#         while True:
#             readSockets, _, exceptionSockets = select.select(connectedSockets, [], connectedSockets)

#             for notifiedSocket in readSockets:
#                 if notifiedSocket == s:
#                     clientSocket, clientAddress = s.accept()
#                     connectedSockets.append(clientSocket)
#                     clientList[clientSocket] = "jbergen"

#                     print(f"Accepted new connection from: {clientAddress}")
#                     # print(f"Current connections: {connectedSockets}")
#                 else:
#                     try:
#                         message = notifiedSocket.recv(1024).decode()
#                         if len(message) == 0:
#                             continue
#                         print(f"Received from {notifiedSocket}: {message}")
#                     except:
#                         break