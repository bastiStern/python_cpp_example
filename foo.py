import struct

class FooBar():

    def __init__(self):
        pass
    
    def process(self, blob, pattern):
        assert isinstance(blob, bytes)
        values = list(struct.unpack(pattern, blob))
        print("Python received values: {}".format(str(values)))
        for i in range(len(values)):
            values[i] += 1
        print("Python sending values: {}".format(str(values)))
        return struct.pack(pattern, *values)
        

def on_construct():
    try:
        print("Construct callback called")
        global foo_obj
        foo_obj = FooBar()
        return foo_obj

    except BaseException as e:
        print("Error im construct callback")
        print(e)
        return None

def on_process(arg):
    try:
        print("Process callback called")
        global foo_obj
        return foo_obj.process(arg, "ifiii")
        
    except BaseException as e:
        print("Error im process callback")
        print(e)
        return None