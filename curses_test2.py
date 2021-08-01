# import curses
# import os

# VERSION = "0.1-dev" #version number

# screen = curses.initscr() #initialize the curses window

# #Configure color pairs for showing select menu options as highlighted
# curses.start_color() #enable color for highlighting menu options
# curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_WHITE) #color pair 1
# highlightText = curses.color_pair(1) #color pair for highlighted menu option
# normalText = curses.A_NORMAL #color pair for non-highlighted menu options

# #Configure global variables for Curses
# curses.noecho() #disable the keypress echo to prevent double input
# curses.cbreak() #disable line buffers to run the keypress immediately
# curses.curs_set(0)
# screen.keypad(1) #enable keyboard use
# screen.addstr(2, 2, "Screen Resize Test" + VERSION, curses.A_UNDERLINE)

# #test screen resize
# def main_screen():
#     escape = False
#     while escape == False:
#         maxY, maxX = screen.getmaxyx()
#         screen.border('|', '|', '-', '-', '+', '+', '+', '+')
#         screen.addstr(4, 2, "MaxY: " + str(maxY))
#         screen.addstr(5, 2, "MaxX: " + str(maxX))

#         x = screen.getch()

#         if x == ord("q"):
#             escape = True
#             curses.endwin()
#         elif x == curses.KEY_RESIZE:
#             screen.erase()
#             screen.addstr(2, 2, "Screen Resize Test" + VERSION, curses.A_UNDERLINE)

# main_screen()

import curses
import os

VERSION = "0.1-dev" #version number

screen = curses.initscr() #initialize the curses window

#Configure color pairs for showing select menu options as highlighted
curses.start_color() #enable color for highlighting menu options
curses.init_pair(1, curses.COLOR_BLACK, curses.COLOR_WHITE) 
curses.init_pair(2, curses.COLOR_CYAN, curses.COLOR_BLACK)
curses.init_pair(3, curses.COLOR_RED, curses.COLOR_BLACK)


highlightText = curses.color_pair(1) #color pair for highlighted menu option
normalText = curses.A_NORMAL #color pair for non-highlighted menu options

#Configure global variables for Curses
curses.noecho() #disable the keypress echo to prevent double input
curses.cbreak() #disable line buffers to run the keypress immediately
curses.curs_set(0)
screen.keypad(1) #enable keyboard use
screen.addstr(2, 2, "Screen Resize Test" + VERSION, curses.A_UNDERLINE)



#test screen resize
def main_screen():
    # Declaration of strings
    statusbarstr = "Press 'q' to exit | STATUS BAR |"

    escape = False
    while escape == False:
        maxY, maxX = screen.getmaxyx()
        screen.border('|', '|', '-', '-', '+', '+', '+', '+')
        screen.addstr(4, 2, "MaxY: " + str(maxY))
        screen.addstr(5, 2, "MaxX: " + str(maxX))

        x = screen.getch()

                # Render status bar
        screen.attron(curses.color_pair(1))
        screen.addstr(maxY-1, 0, statusbarstr)
        screen.addstr(maxY-1, len(statusbarstr), " " * (maxY - len(statusbarstr) - 1))
        screen.attroff(curses.color_pair(3))

        if x == ord("q"):
            escape = True
            curses.endwin()
        elif x == curses.KEY_RESIZE:
            screen.erase()
            screen.addstr(2, 2, "Screen Resize Test" + VERSION, curses.A_UNDERLINE)

main_screen()