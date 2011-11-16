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
        #m = Message("Boston")
        #content = {"hello":"India","kdas":"Still have to learn a lot"}
        #content['data'] = {"City":"Pune"}
        #content['nicks'] = ["kushal","mether","mbuf"]
        content = {}
        content["dictval"] = {"owner": "kdas"}
        content["listval"] = ["mbuf","pjp",{'1':"first",'2':"second",'3':"third"}]
        m = Message(content=content)
        snd.send(m)
    except SendError, e:
        print e
    if snd is not None:
        snd.close()

except KeyboardInterrupt:
    pass

conn.close()
