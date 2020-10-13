from random import *
'''
q_ui=[]
for i in range(12,32):
	q_ui.append(2**i)
q_li=[]
for i in range(12):
	q_ui.append(2**i)
'''
'''
reg_tab=["zero","ra","sp","gp","tp"]
for i in range(3):
	reg_tab.append("t"+str(i))
for i in range(2):
	reg_tab.append("s"+str(i))
for i in range(8):
	reg_tab.append("a"+str(i))
for i in range(2,12):
	reg_tab.append("s"+str(i))
for i in range(3,7):
	reg_tab.append("t"+str(i))
'''
al=""
rt=[];
plik=open("./ioasm/testlui2.s",'w')
plik2=open("./iocmp/testlui2_p",'wb')

plik.write("\t.globl _start\n_start:\n")
for i in range(1,32):
	a=randrange(1,2**20)
	a*=2**12
	plik2.write((a).to_bytes(4,byteorder='little'))
	plik.write("\tlui x"+str(i)+", %hi("+str(a)+")\n")
plik.write("end:\n\tj end")
plik.close()
plik2.close()


plik=open("./ioasm/testaddi1.s",'w')
plik2=open("./iocmp/testaddi1_p",'wb')

plik.write("\t.globl _start\n_start:\n")
for i in range(1,32):
	a=randrange(1,2**12)
	plik2.write((a).to_bytes(4,byteorder='little'))
	plik.write("\taddi x"+str(i)+",x0, %lo("+str(a)+")\n")
plik.write("end:\n\tj end")
plik.close()
plik2.close()



'''


def alltestlui(nrit):
	im=randrange(0,(2**32)-1)
	



def testlui(rd,val):
	
'''
