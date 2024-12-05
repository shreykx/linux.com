import ctypes

lib = ctypes.CDLL('./libruncommand.so')


def run_command(command : str):
    lib.run.argtypes = [ctypes.c_char_p]
    lib.run.restype = ctypes.c_char_p
    output = lib.run(command.encode('utf-8')) 
    return output.decode('utf-8')
    