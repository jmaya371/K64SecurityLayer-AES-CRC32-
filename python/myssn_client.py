#myssn_client.py
# Based on the client from https://pymotw.com/3/socket/tcp.html

import myssn
import sys

SERVER_ADDRESS = '169.254.83.130'

Msgs= ["Josue David",
		"Maya Padilla",
		"ITESO",
		"Instituto Tecnológico y de Estudios Superiores de Occidente",
		"Especialidad en Sistemas Embebidos",
		"DESARROLLO DE SOFTWARE DE COMUNICACIONES EN AMBIENTES EMBEBIDOS", 
		"Practica 1",
		"Desarrollo de capas de comunicacion TCP"]
try:
    client = myssn.client_connect(SERVER_ADDRESS)
    while True:
        try:
            # Send data
            for i in range(0, len(Msgs)):
                # bytes_msg = string_msg.encode()
                print(f'*******************Numer Package {i + 1}*******************')
                bytes_msg = Msgs[i].encode()
                myssn.send(client, bytes_msg)
                # Look for the response
                dat = myssn.recv(client)
                if dat:
                    #print('DATA Recived: {!r}'.format(dat))
                    print("\n\n")
                else:
                    print('INFO: closing socket')
                    myssn.close(myssn)
                    break

        except:
            print('INFO: Client Exception')
            break

except ConnectionRefusedError:
    print('INFO: The server is not available')
finally:
    print('INFO: Bye!')

