import Main
import pygame
import os
from Hints import Hints
from Helpers.Helpers import drawTextInCenter
config = Main.config

newHint = ""
resolution = (0,0)
screen: pygame.surface.Surface = ""
def setupHints():
    #add every event controlled by this controller to status array
    #Example:
    #status["p"]["event id"] = 1; //status op hints are saved here
    #status["pi"]["event id"] = "[2, 4, -8, 3, 2]"; //inputs of hints are saved here
    pass
    os.environ["DISPLAY"] = ":0"
    pygame.init()
    Hints.screen = pygame.display.set_mode((0, 0), pygame.FULLSCREEN)
    Hints.resolution = pygame.display.get_window_size()
    screen.fill((0, 0, 0))
    pygame.mouse.set_visible(False) # Hide cursor here
    pygame.display.update()
    

def resetHints():
    pass #handle resetting all hints

#called every loop
def checkHints():
    pass #handle event stuff here button press etc
    if newHint != "":
        screen.fill((0, 0, 0))
        font = pygame.font.Font('Hints/Font/KingdomHeroDemoRegular.ttf', 80)
        
        size = screen.get_size()
        width = size[0] * 0.8
        height = size[1] * 0.8
        
        textSurface = pygame.surface.Surface((width, height))
        textRect = textSurface.get_rect()
        
        drawTextInCenter(textSurface, newHint, (255,255,255), textRect, font, 2, True)
        
        textRect.center = (resolution[0] // 2, resolution[1] // 2)
        
        screen.blit(textSurface, textRect)
        
        pygame.display.update()
        Hints.newHint = ""
    

#called when a hint is received
#only save data needed for hint update stuff in checkHints()
def receivedHint(type, hint):
  #handle receiving hint
  pass
  Hints.newHint = hint
  

