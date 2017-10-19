# Copyright (C) 2016 raodm@miamiOH.edu

# A simple implementation of an Ackermann method.

import sys
import resource

# Do an ugly, ugly hack to adjust stack sizes in powers of 2.
# NOTE: Will not work on Mac.  Wait! Python is portable, right?
resource.setrlimit(resource.RLIMIT_STACK, (2**32,-1))
sys.setrecursionlimit(10**6)

def Ack(M, N):
    if (M > 0):
        if (N > 0):
            return Ack(M-1, Ack(M, N-1))
        else:
            return Ack(M-1, 1)
    else:
        return N+1

# The main part of the code (written in standard Python style)
if __name__ == "__main__":
    n = 1 if (len(sys.argv) < 2) else int(sys.argv[1])
    print "Ack(3,", n, "): ", Ack(3, n)

# End of script
