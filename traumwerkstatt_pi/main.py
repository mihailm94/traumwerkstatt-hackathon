import time
import serial
import thingspeak
from multiprocessing import Queue, Process
import argparse
import json
import sys

# Serial - port, baud
ser = serial.Serial('/dev/ttyUSB0', 9600)

# ThingSpeak
channel_id = 1256278
write_api_key = '46F35S8XA7HPQ4DH'
read_api_key = 'I3DZBXU4KBGHBHQ9'
channel = thingspeak.Channel(id=channel_id, write_key=write_api_key, api_key=read_api_key)

# Global user id
# user_id_preset = 0

# Array of processes
procs = []

# A queue for IPC
queue = Queue()

def setThingspeak(usr_id):
    
    try: 
        while 1 :
            
            # Read from serial. Blocking!
            user_id_serial = ser.read() 

            # Arduino is set up so that when user clicks button,
            # it always sends a "0" (int) over the Serial connection
            if( 0 == int(user_id_serial) ):
                print("Receive button press from Serial")
                # Push to Thingspeak server
                channel.update({ 'field1': usr_id })

    except KeyboardInterrupt:
        return

"""
def getThingspeak():
    
    try:
        while 1 :        
            
            jread = json.loads(channel.get({}))
            
            # Array might be empty. Indexing the -1 element throws an indexing error in this way
            if len(jread['feeds']) != 0:
                # Get last element of array. If empty, returns empty list, not exception
                juser = jread['feeds'][-1]['field1']
                print(json.dumps(jread, indent=4))
    
            # free accounts have a time limit
            time.sleep(15)
    
    except KeyboardInterrupt:
        return
"""
def main():
    
    # main.py is called with a trailing string specifying your user id
    n = len(sys.argv)
    if( 1 >= n ):
        print "Missing argument - String with username. Example: python main.py \"Mr. Brown\""
        quit()
    
    user_id_preset = str(sys.argv[1])
    print "Hello " + user_id_preset
    
    setThingspeak(user_id_preset)


"""
    # Start 2 processes
    process = Process(target=setThingspeak)
    process.start()
    procs.append(process)
    
    process = Process( target=getThingspeak )
    process.start()
    procs.append(process)

    for p in procs:
        p.join()
"""

if __name__ == "__main__":
    main()
