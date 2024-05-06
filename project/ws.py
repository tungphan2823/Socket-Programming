#!/usr/bin/env python

import asyncio		#asynchronous
import datetime		#get time stamp
import random		#make random number
import websockets		#main stuff

async def myServ(ws, path): 	# server function
    while True:
        now = 'e2101068' + datetime.datetime.utcnow().isoformat()
        await ws.send(now)
        await asyncio.sleep(1 + random.random() * 3)

# create a server 
start_server = websockets.serve(myServ, 'localhost', 11111)

# start the server and run forever
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
