#!/usr/bin/env python

from pprint import pprint
from qpid.messaging import *
broker =  "localhost:5672"

conn = Connection(broker)
addr = "amq.topic"

try:
    conn.open()
    ssn = conn.session()
    snd = None
    try:
        snd = ssn.sender(addr)
        m = Message(content="the date")
        m.subject = "19th Feb, 2009"
        m.user_id = "voldemort"
        m.priority = 7
        snd.send(m)
    except SendError, e:
        print e
    if snd is not None:
        snd.close()
except KeyboardInterrupt:
    pass

conn.close()
