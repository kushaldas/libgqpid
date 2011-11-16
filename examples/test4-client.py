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
    rcv = ssn.receiver(addr)
    msg = rcv.fetch()
    pprint(msg.content)
    ssn.acknowledge()
except ReceiveError, e:
    print e
except KeyboardInterrupt:
    pass

conn.close()
