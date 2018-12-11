#!/usr/bin/env python

import Tkinter as tk
from PIL import ImageTk, Image
from tkFileDialog import askopenfilename
import subprocess
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

def callback(n):
	name = askopenfilename()
	file = open(name, 'r')
	x = file.read()
	if len(x) > 1:
		if n == 1:
			buff = 'veiculos.txt'
		elif n == 2:
			buff = 'eventos.txt'
		file_d = open(buff, 'r+')
		file_d.truncate(0)
		file_d = open(buff, 'w')
		file_d.write(x)
	file.close()

def answer():
	subprocess.call("./main", shell = True)
	os.system("open saida.txt")

path = "interface2.png"
window = tk.Tk()
window.wm_title("SISTEMA DE TRANSITO")
canvas = tk.Canvas(window, width = 636, height = 357);
canvas.pack()
img = Image.open(path)
img = img.resize((636,357), Image.ANTIALIAS)
photoImg = ImageTk.PhotoImage(img)
canvas.create_image(318, 178, image = photoImg)
initiate_button = tk.Button(window, text = "Iniciar", command = answer, anchor = 'w', width = 10, activebackground = "#33B5E5")
initiate_button_window = canvas.create_window(318, 315, anchor = 'center', window = initiate_button)
veiculos_button = tk.Button(window, text = "Veiculos", command = lambda: callback(n = 1), anchor = 'w', width = 10, activebackground = "#33B5E5")
veiculos_button_window = canvas.create_window(158, 315, anchor = 'center', window = veiculos_button)
eventos_button = tk.Button(window, text = "Eventos", command = lambda: callback(n = 2), anchor = 'w', width = 10, activebackground = "#33B5E5")
eventos_button_window = canvas.create_window(478, 315, anchor = 'center', window = eventos_button)

window.mainloop()
