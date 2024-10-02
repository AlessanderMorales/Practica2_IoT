import socket
import os
from _thread import *


HOST = '192.168.92.152'  # Cambia a la IP de tu servidor
PORT = 8000
server = socket.socket()
server.bind((HOST, PORT))
server.listen(5)
distance = 0
def funcionalidad(connection):
    global distance
    try:
        while True:
            data = connection.recv(2048).decode('utf-8')
            if data != '':
                print(f"CLIENT SENDS: {data}")
                if data.startswith('distance='):
                    distance = float(data[9:])
                    print(f"Distance: {distance} cm")
                elif data.startswith('GET'):
                    connection.sendall((str(distance) + "\n").encode())
                else:
                    print("Datos incorrectos")
                    break
    except Exception as e:
        print(f"Error en la funcionalidad: {e}")
    finally:
        connection.close()


while True:
    client, addr = server.accept() 
    print(f"Conexión entrante desde {addr[0]}:{addr[1]}")
    start_new_thread(funcionalidad, (client,))
