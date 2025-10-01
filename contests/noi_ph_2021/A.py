hlist = []
maxhr = -1
index = 0
 
for i in range(10):
    heartrate = int(input())
    hlist.append(heartrate)
 
for i in range(len(hlist)):
    if hlist[i] >= maxhr:
        index = i
        maxhr = hlist[i]
 
if index == 0:
    manlilinlang = "ITIM"
elif index == 1:
    manlilinlang = "PUTI"
elif index == 2:
    manlilinlang = "PULA"
elif index == 3:
    manlilinlang = "BUGHAW"
elif index == 4:
    manlilinlang = "DILAW"
elif index == 5:
    manlilinlang = "LUNTIAN"
elif index == 6:
    manlilinlang = "TSOKOLATE"
elif index == 7:
    manlilinlang = "LILA"
elif index == 8:
    manlilinlang = "DALANDAN"
elif index == 9:
    manlilinlang = "LUNTIAN PERO MEDYO DILAW"
 
print("SI " + manlilinlang + " AY SINIPA PALABAS.")