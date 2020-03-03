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


#Params
res = [c_point, c_int, Size, c_float, c_bool]
args = [[Size, c_float, c_int], [c_point, c_point], [c_point],
        [c_point, c_float], [c_point, c_int, c_int], [Size, c_point]]


#Pre formed func defs
#Format name : (res, args)
funcs = {"newMat":(0,0), "mult":(0,1), "add":(0,1), "sub":(0,1), "equ":(4,1), "del":(4,2),
         "sca":(0,3), "getSize":(2,2), "getValue":(3,4), "generate":(0,5)}


#Define funcs
for k,v in funcs.items():
    fres = res[v[0]]
    fargs = args[v[1]]
    p = ctypes.WINFUNCTYPE(fres, *fargs)
    funcs[k] = p((k, clib))


#Cleanup
del path, clib, c_int, c_point, c_bool
del res, args, k, v, fres, fargs, p
toPointer = ctypes.pointer
del pathlib, ctypes
#Keeping c_float and ctypes.pointer for toFloatP func


#Util
def toFloatP(length, inp):
    fa = (c_float * length)(*inp)
    return toPointer(fa)


class Matrix:
    def __init__(this, size, dat = None):
        if dat == None: #Must be just a pointer
            if not size:
                raise Exception("Null pointer: Produced by invalid process")
            this.pointer = size
        elif type(dat) == list and type(size) == tuple:
            length = size[0] * size[1]
            this.pointer = funcs["generate"](Size(size[0], size[1]), toFloatP(length, dat))
        elif type(size) == tuple:
            this.pointer = funcs["newMat"](Size(size[0], size[1]), dat, False)
        else:
            raise Exception("eek")
        

    def getValue(this, *pos):
        return funcs["getValue"](this.pointer, pos[0], pos[1])


    def getSize(this):
        siz = funcs["getSize"](this.pointer)
        return siz.height, siz.width


    def __eq__(this, that):
        if type(that) != Matrix:
            return False
        return funcs["equ"](this.pointer, that.pointer)


    def __add__(this, that):
        if type(that) != Matrix:
            raise Exception("Invalid type")
        return Matrix(funcs["add"](this.pointer, that.pointer))


    def __sub__(this, that):
        if type(that) != Matrix:
            raise Exception("Invalid type")
        return Matrix(funcs["sub"](this.pointer, that.pointer))


    def __mul__(this, that):
        if type(that) == Matrix:
            return Matrix(funcs["mult"](this.pointer, that.pointer))
        elif not type(that) in [int, float, complex]:
            raise Exception("Invalid type")
        return Matrix(funcs["sca"](this.pointer, that))


    def __neg__(this):
        return Matrix(funcs["sca"](this.pointer, -1))


    def __pos__(this):
        return this #Dont gen new or python will prematurely delete data


    def __del__(this):
        funcs["del"](this.pointer)


    def __repr__(this):
        return "Matrix" + str(this.getSize())


    
