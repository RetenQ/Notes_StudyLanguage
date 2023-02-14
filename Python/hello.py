'A test Modle'  
__author__ = 'R'    

import sys

def test():
    args = sys.argv 
    if len(args) == 1 :
        print('Hello World')
    elif len(args) == 2 :
        print('Hi , %s !' % args[1])
    else:
        print("Too many args")

if __name__ == '__main__':
    test()
    
