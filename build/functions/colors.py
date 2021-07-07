#!/usr/bin/env python
#
# functions.py : 
#             useful functions for the python modules in this folder
#
# Copyright © Noé Perard-Gayot 2020.                                                                                        #
# Licensed under the MIT License. You may obtain a copy of the License at https://opensource.org/licenses/mit-license.php   #
#


#
#  colors for formating text
#
class color:
    HEADER  = '\033[1;35;68m'
    OKBLUE  = '\033[0;7;34m' 
    OKGREEN = '\033[0;39;32m'
    WARNING = '\033[0;93;14m'
    ERROR   = '\033[6;41;62m'
    LESS    = '\033[2;9;11m'
    ENDC    = '\033[0m'  

    @classmethod
    def print(cls, text : str, style : str , end = '\n'):
        '''
        adapt output to a color
        '''
        print( style + text + cls.ENDC, end = end)



def _print_format_table():
    """
    prints table of formatted text format options
    """
    from random import randrange
    s = randrange(100)
    f = randrange(100)
    b = randrange(100)
    for style in range(s, s + 8):
        for fg in range(f,f + 8):
            s1 = ''
            for bg in range(b,b+8):
                format = ';'.join([str(style), str(fg), str(bg)])
                s1 += '\x1b[%sm %s \x1b[0m' % (format, format)
            print(s1)
        print('\n{}'.format(color.ENDC))


def _print_colors():
    """
    prints table of formatted text format options
    """
    color.print("HEADER  = {} ".format(repr(color.HEADER)),  color.HEADER  )
    color.print("OKBLUE  = {} ".format(repr(color.OKBLUE)),  color.OKBLUE  )
    color.print("OKGREEN = {} ".format(repr(color.OKGREEN)), color.OKGREEN )
    color.print("WARNING = {} ".format(repr(color.WARNING)), color.WARNING )
    color.print("ERROR   = {} ".format(repr(color.ERROR)),   color.ERROR   )
    color.print("LESS    = {} ".format(repr(color.LESS)),    color.LESS)
    color.print("ENDC    = {} ".format(repr(color.ENDC)),    color.ENDC)


if __name__ == "__main__":
    _print_format_table()
    _print_colors()