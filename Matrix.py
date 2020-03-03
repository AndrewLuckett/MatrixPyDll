import ctypes
import pathlib

#Load lib
path = str(pathlib.Path().absolute())
clib = ctypes.CDLL(path+"/Matrix.dll")

#TYPES
c_int = ctypes.c_int
c_point = ctypes.c_void_p
c_float = ctypes.c_double
c_bool = ctypes.c_bool
class Size(ctypes.Structure):
    _fields_ = [("height", c_int), ("width", c_int)]

    def __repr__(this):
        return "Size(" + str(this.height) + ", " + str(this.width) + ")"

def toFloatP(length, inp):
    fa = (c_float * length)(*inp)
    return ctypes.pointer(fa)

#Params
res = [c_point, c_int, Size, c_float, c_bool]
args = [[Size, c_float, c_int], [c_point, c_point],
        [c_point], [c_point, c_float], [c_point, c_int, c_int], [Size, c_point]]


#Pre formed func defs
#Format name : (res, args)
funcs = {"newMat":(0,0),"mult":(0,1),"add":(0,1),"sub":(0,1),"equ":(4,1),"del":(4,2),
         "neg":(0,2),"sca":(0,3),"getSize":(2,2),"getValue":(3,4),"generate":(0,5)}


#Define funcs
for k,v in funcs.items():
    fres = res[v[0]]
    fargs = args[v[1]]
    p = ctypes.WINFUNCTYPE(fres,*fargs)
    funcs[k] = p((k,clib))

#Cleanup
del path, clib, c_int, c_point, c_bool
del res, args, k, v, fres, fargs, p
del pathlib
#Keeping c_float and ctypes for toFloatP func

class Matrix:
    def __init__(this, size, dat):
        if type(dat) == list:
            length = size[0] * size[1]
            this.pointer = funcs["generate"](Size(size[0], size[1]), toFloatP(length, dat))
        else:
            this.pointer = funcs["newMat"](Size(size[0], size[1]), dat, False)
        

    def getValue(this, *pos):
        return funcs["getValue"](this.pointer, pos[0], pos[1])

    def getSize(this):
        siz = funcs["getSize"](this.pointer)
        return siz.height, siz.width

    def __del__(this):
        funcs["del"](this.pointer)


    
