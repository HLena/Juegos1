import random
import numpy
from numba import njit
from timeit import timeit

#=============================   Word Count   =============================
def generate_file():
    words = ['CienciaComputacion', 'hola mundo', 'cs2019', 'Arequipa','peru','lunes','Cloud']
    file = open("texto1.txt","w+")
    for i in range(100000000):
        r = random.randint(0, len(words)-1)
        # print(r)
        file.write(words[r] + " ")
    file.close
    print("final")


def CountWords():
    dic = dict()
    file = open('words1.txt','r')
    for line in file:
        #print(line)
        words = line.split()
        for w in words:
            if w in dic:
                dic[w] +=1
            else:
                dic[w]=1
    # print(timeit())
    print(dic)
    


# generate_file()
CountWords()
#================================   Eejmplo palaralelizacion ====================

# x = numpy.random.random((1000,1000))
# y = numpy.random.random((1000,1000))

# def do_trig(x,y):
#     z = numpy.sin(x**2) + numpy.cos(y)
#     return z
# do_trig_jit_par = njit(parallel = True)(do_trig)


#===================================================================0
