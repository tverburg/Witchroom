import psutil

def freeMemory():

    memory = psutil.virtual_memory()

    return memory.available