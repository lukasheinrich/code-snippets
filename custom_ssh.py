#!/usr/bin/env 

import paramiko
import termios
import sys
import tty
import socket
from paramiko.py3compat import u

import click


def posix_shell(chan):
    import select
    
    oldtty = termios.tcgetattr(sys.stdin)
    try:
        tty.setraw(sys.stdin.fileno())
        tty.setcbreak(sys.stdin.fileno())
        chan.settimeout(0.0)

        while True:
            r, w, e = select.select([chan, sys.stdin], [], [])
            if chan in r:
                try:
                    x = u(chan.recv(1024))
                    if len(x) == 0:
                        # sys.stdout.write('\r\n exiting... \r\n')
                        break
                    sys.stdout.write(x)
                    sys.stdout.flush()
                except socket.timeout:
                    pass
            if sys.stdin in r:
                x = sys.stdin.read(1)
                if len(x) == 0:
                    break
                chan.send(x)

    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, oldtty)
        # print "bye"

@click.group()
def cliapp():
    pass

@cliapp.command()
@click.argument('user')
@click.argument('password')
@click.argument('host')
@click.argument('port')
def shell(user,password,host,port):
    click.secho('login', fg = 'green')
    ssh = paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
  
    ssh.connect(host, username=user, password=password, port = int(port))

    posix_shell(ssh.invoke_shell())
    click.secho('bye bye.. ', fg = 'green')

if __name__ == '__main__':
    cliapp()

