import tkinter
import random
from pygame import mixer
from tkinter import *
import tkinter.font as font
from tkinter import filedialog
import os
from PIL import ImageTk, Image
from itertools import count, cycle
import serial, time, json
from serial import Serial

os.chdir(os.path.dirname(os.path.abspath(__file__)))

ser = serial.Serial('COM8', 115200, xonxoff=False, rtscts=False, dsrdtr=False) #Tried with and without the last 3 parameters, and also at 1Mbps, same happens.

#Establecer estructura Node para las canciones y sus funciones
class Node:
    def __init__(self, key, song, artist, genre, filename, cover) -> None:
        super().__init__()
        self.left = None
        self.right = None
        self.val = key
        self.song = song
        self.artist = artist
        self.genre = genre
        self.filename = filename
        self.cover = cover
        #self.next = next
        #self.prev = prev
        
    def __str__(self) -> str:
        return f"{self.song}, {self.artist}, {self.genre}, {self.filename},{self.cover}"
    
    def __getattribute__(self, name: str) -> str:
        if name == "song":
            p = super().__getattribute__(name)
            return str(p)
        elif name == "artist":
            p = super().__getattribute__(name)
            return str(p)
        elif name == "genre":
            p = super().__getattribute__(name)
            return str(p)
        return str(super().__getattribute__(name))
    
    def __getattr__(self, name : str) -> str:
        return name + "no es valido"
#Código para la animación  
class ImageLabel(tkinter.Label):
    
    def load(self, im):
        if isinstance(im, str):
            im = Image.open(im)
            frames = []
        try:
            for i in count(1):
                frames.append(ImageTk.PhotoImage(im.copy()))
                im.seek(i)
                
                
        except EOFError:
            pass
        self.frames = cycle(frames)

        try:
            self.delay = im.info['duration']
        except:
            self.delay = 100

        if len(frames) == 1:
            self.config(image=next(self.frames))
        else:
            self.next_frame()


    def unload(self):
        self.config(image=None)
        self.frames = None

    def next_frame(self):
        #data_raw = ser.readline()
        #print(data_raw)
        #if (data_raw == b'\x001\r\n'):
        #    mixer.music.pause()
        if self.frames:
            self.config(image=next(self.frames))
            self.after(self.delay, self.next_frame)

#Cargar información a los Nodes
s1 = Node(1,"Shallow","Lady Gaga","Pop Rock","1_Shallow_LadyGaga_PopRock.mp3","shallow_cover.png")
s2 = Node(2, "Hentai","Rosalía","Pop Ballad", "2_Hentai_Rosalia_PopBallad.mp3","motomami_cover.jpg")
s3 = Node(3, "ARTPOP","Lady Gaga","Electro Pop", "3_ARTPOP_LadyGaga_ElectroPop.mp3","artpop_cover.jpg")
s4 = Node(4, "BohemianRhapsody","Queen","Rock","4_BohemianRhapsody_Queen_Rock.mp3","queen_cover.jpg")
#Meter Nodes a un array
array = [s1,s2,s3,s4]
array2 = ['DhqB.gif','giphy.gif','gradient.gif','bg_75.gif']

#CONTROL DE QUE CANCION ESTA SELECCIONADA
def playSong():
    mixer.music.load(array[i].filename)
    mixer.music.play()

#índice
global i
i = 0

#inicializar reproductor y poner la primera canción

mixer.init()
playSong()

#funciones para controlar la canción reproducida
def Pause():
    mixer.music.pause()

def Play():
    mixer.music.unpause()

def Next():
    global i
    i = i + 1
    playSong()
    setInfo()
    time.sleep(1)
    
def Prev():
    global i
    i= i - 1
    playSong()
    setInfo()
    time.sleep(1)
    
#función para cambiar información    
def setInfo():
    songtitle.config(text = str(array[i].song))
    songartist.config(text = str(array[i].artist))
    songgenre.config(text = str(array[i].genre))
    image()
    mainpage.update()
#función para cambiar imagen   
def image():
    imagen = Image.open(str(array[i].cover))
    resized = imagen.resize((250,250),Image.Resampling.LANCZOS)
    new_imagen = ImageTk.PhotoImage(resized)
    coverart.config(image = new_imagen)
    coverart.image=new_imagen
    mainpage.update()

def check(x):
    global ser
    
    if ser.isOpen() and ser.in_waiting:
        ser.flushInput()
        ser.flushOutput()
        data_raw = ser.readline()
        print(data_raw)

        if(data_raw == b'\x001\r\n'):
            #Pausa
            
            if x==1:
                x=2
            elif x==2:
                x=1
            if x==2:
                print(x)
                Pause()
                time.sleep(1)
            if x==1:
                print(x)
                Play()
                time.sleep(1)
                
        elif (data_raw == b'\x002\r\n'):
            #Play
            print("eeeeh")
        elif (data_raw == b'\x004\r\n'):
            #Next
            Next()
            time.sleep(1)
        elif (data_raw == b'\x008\r\n'):
            #Prev
            Prev()
            time.sleep(1)
        return x

##ESTABLECER VENTANA TINKER
mainpage = tkinter.Tk()
mainpage.geometry("480x1080")
#background
mainpage.configure(bg='black')
##ESTABLECER COVER ART (IMAGEN)
coverart = Label(mainpage, image = "",bg='#000000')
coverart.pack(anchor=CENTER)
image()
#ESTABLECER LABELS E INFO
songtitle = tkinter.Label(mainpage, text = str(array[i].song), bg='#000000', fg='#BF3EFF', pady=10, padx=10)
songtitle.pack(anchor = CENTER)
songtitle.config(font=("Eras Demi ITC",50))
songartist = tkinter.Label(mainpage, text = str(array[i].artist),bg='#000000', fg='#FF1493', pady=10, padx=10)
songartist.pack(anchor = CENTER)
songartist.config(font=("Eras Demi ITC",40))
songgenre = tkinter.Label(mainpage, text = str(array[i].genre),bg='#000000', fg='#FF7F00', pady=10, padx=10)
songgenre.pack(anchor = CENTER)
songgenre.config(font=("Eras Demi ITC",30))
#Botones
#Pause_botton = tkinter.Button(mainpage, text ="Pause", command = Pause)
#Pause_botton.pack(side=BOTTOM)
#Play_botton = tkinter.Button(mainpage, text ="Play", command = Play)
#Play_botton.pack(side=BOTTOM)
#Prev_botton = tkinter.Button(mainpage, text ="Prev", command = Prev)
#Prev_botton.pack(side=BOTTOM)
#Next_botton = tkinter.Button(mainpage, text ="Next", command = Next)
#Next_botton.pack(side=BOTTOM)
#Se actualiza
setInfo()
#check()
#SERIAL


x=2
#
#BACKGROUND
lbl = ImageLabel(mainpage, bg='#000000')
lbl.pack(anchor= CENTER)
lbl.load(array2[i])
while True:
    mainpage.update()
    x=check(x)