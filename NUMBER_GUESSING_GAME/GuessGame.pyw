from tkinter import *
import tkinter.messagebox as msg
import random as rand
def generate():
    global num 
    num=rand.randrange(1,100)
    print(num)
def check():
    global trial
    user=int(Num.get())
    if user > num :
        option=msg.askretrycancel("WRONG ANS",f"{user} Is Wrong Ans\nTry Some Lower Guess")
        trial = trial + 1
        if option == True:
            Num.delete(0,END)
        else :
            pass
    elif user < num :
        option=msg.askretrycancel("WRONG ANS",f"{user} Is Wrong Ans\nTry Some Higher Guess")
        trial = trial + 1
        if option == True:
            Num.delete(0,END)
    else:
        msg.showinfo("Congratulation",f"YOU Won The Game By {trial} Trial ")
        option=msg.askyesno("Congratulation","DO You Want to Play Again")
        if option == True:
            trial=0
            Num.delete(0,END)
            generate()
        else:
            exit()
def Enter_Button(event):
    check()
generate()
root=Tk()
trial=1
H,W=250,420
BG='RED'
root.title("Guess Game")
root.minsize(W,H)
root.maxsize(W,H)
root['bg']=[BG]
# guess=Label(text="Guess The Number Between 1 to 100",fg="RED",font=("regular",18,""))
IMAGE=PhotoImage(file="Sample2.png",width=400)
guess=Label(root,image=IMAGE,bg=BG)
guess.grid(column=0,row=0,columnspan=3)
Num=Entry(textvariable=IntVar,font=("regular",10,""))
Num.grid(column=1,row=1,padx=10,pady=10)
GO=Button(text="GO",bg="GREEN",fg="WHITE",command=check,padx=10,pady=10,relief="sunken",borderwidth=3)
GO.grid(column=1,row=3)
root.bind('<Return>',Enter_Button)
root.mainloop()