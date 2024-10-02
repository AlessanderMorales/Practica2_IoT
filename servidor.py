import socket
import os
from _thread import *

# Configuración del servidor
HOST = '192.168.1.66'  # Cambia a la IP de tu servidor
PORT = 8000
server = socket.socket()
server.bind((HOST, PORT))
server.listen(5)
distance = 0  # Variable global para almacenar la distancia recibida

# Función para manejar cada conexión entrante
def funcionalidad(connection):
    global distance
    try:
        while True:
            # Recibir datos del cliente (ESP32)
            data = connection.recv(2048).decode('utf-8')
            if data != '':
                print(f"CLIENT SENDS: {data}")
                
                # Si el ESP32 sensor envía la distancia
                if data.startswith('distance='):
                    distance = float(data[9:])  # Extraer el valor de distancia
                    print(f"Distance: {distance} cm")
                
                # Si el ESP32 actuador solicita la distancia (GET)
                elif data.startswith('GET'):
                    connection.sendall((str(distance) + "\n").encode())  # Enviar la distancia al ESP32 actuador
                else:
                    print("Datos incorrectos")
                    break
    except Exception as e:
        print(f"Error en la funcionalidad: {e}")
    finally:
        connection.close()

# Bucle principal del servidor
while True:
    client, addr = server.accept()  # Aceptar una nueva conexión
    print(f"Conexión entrante desde {addr[0]}:{addr[1]}")
    start_new_thread(funcionalidad, (client,))  # Crear un hilo para manejar la conexión
