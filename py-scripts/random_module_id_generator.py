import random

def random_module_id_generator():
    frst  = random.randint(0, 255)
    scnd  = random.randint(0, 255)
    thrd  = random.randint(0, 255)
    frth  = random.randint(0, 255)
    ffth  = random.randint(0, 255)

    return '=\"0x50 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}\"'.format(frst, scnd, thrd, frth, ffth)

n = int(input("Enter Value of n: "))

for i in range(0, n):
    print(random_module_id_generator())