import argparse
import socket


# task 1: using socket to GET a file
def task1():
    """
    prints message within the terminal
    """
    HOST  = "gaia.cs.umass.edu"
    PORT = 80  # HTTP port #

    # TCP 
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    tcp.connect((HOST, PORT))  # connects to Web

    # sends Http request
    http_req = "GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n"

    tcp.send(http_req.encode())

    #  GET response using a single recv command
    GET = tcp.recv(1024)

    #  close socket and end

    tcp.close()

    # prints response and message
    print('Request: {}'.format(GET))
    print('[RECV] - {}\n'.format(len(GET)))
    print(GET.decode())

# task 2: get data for a large file

def task2():
    """
    Requests a large html object. Compared to task 1, added in an additional loop to take the
    request in sections. 
    """

    HOST = "gaia.cs.umass.edu"
    PORT = 80  # HTTP port number

    # TCP 
    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    tcp.connect((HOST, PORT))  # connects to Web

    # sends Http request
    http_req = "GET /wireshark-labs/HTTP-wireshark-file3.html HTTP/1.1\r\nHost:gaia.cs.umass.edu\r\n\r\n"

    tcp.send(http_req.encode())

    # extra variable to account for a larger filesize

    # For larger HTTP requests, the foloowing loop helps handle the larger size of the request

    section = tcp.recv(1024)
    http_response = section

    while True:
        section = tcp.recv(1024)
        http_response += section
        if not section:
            break 
        
    print('Request: {}'.format(http_req))
    print('[RECV] - {}'.format(len(http_response)))
    print(http_response.decode())
    tcp.close()

# task 3: World's simplest HTTP server
def task3():
    """
    Creates http server and connects to the web
    """

    tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # define server address
    address = ('0.0.0.0', 23423) 

    # sets up the html text and output for program
    data = "HTTP/1.1 200 OK\r\n"\
                    "Content-Type: text/html; charset=UTF-8\r\n\r\n"\
                    "<html>Congratulations! You've downloaded the first Wireshark lab file!</html>\r\n"
    
    tcp.bind(address)

    # listens for connection
    tcp.listen(5)
    print("listening, browse to http://127.0.0.1:23423")

    while True:
        c, address = tcp.accept()
        received_con = c.recv(1024)
        print("Recieved: {}".format(received_con))
        print("sending...")
        print(data)
        c.send(bytes(data, 'utf8'))
        c.close
        break


# imported the argparse module to help call each individual task
# https://docs.python.org/3/library/argparse.html
def main():
    parser = argparse.ArgumentParser(usage='python http_server.py -case {1, 2, 3}', formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('-task', required=True, choices=range(1,4), type=int,
            help="test case number:\n1 - small http file\n2 - large http file\n3 - http server\n")
    args = parser.parse_args()
    
    if args.task == 1:
        print("Running Small HTTP Request...")
        task1()
    elif args.task == 2:
        print("Running Large HTTP Request...")
        task2()
    else: 
        print("Runnning Simple HTTP Server...")
        task3()
    
if __name__ == "__main__":
    main()
