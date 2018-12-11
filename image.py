import Tkinter as tk
from PIL import ImageTk, Image
import subprocess
import os

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

window.mainloop()