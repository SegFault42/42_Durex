#i = 0
#while (i < 255):
    #print "\033[" + str(i) + "m" + "Hello"
    #i = i + 1

import time

i = 0
while (i < 255):
    print "\033[38;5;" + str(i) + "m" + "Hello"
    i = i + 1
    #time.sleep(1)
