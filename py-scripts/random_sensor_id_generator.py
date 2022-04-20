import random

def random_sensor_id_generator():
    frst  = random.randint(0, 255)
    scnd  = random.randint(0, 255)
    thrd  = random.randint(0, 255)
    frth  = random.randint(0, 255)
    ffth  = random.randint(0, 255)
    sxth  = random.randint(0, 255)
    svnth = random.randint(0, 255)

    return '=\"0x28 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X} 0x{:02X}\"'.format(frst, scnd, thrd, frth, ffth, sxth, svnth)

n = int(input("Enter Value of n: "))

for i in range(0, n):
    print(random_sensor_id_generator())