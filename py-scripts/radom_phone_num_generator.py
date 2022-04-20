import random

def random_phone_num_generator():
    frst = str(random.randint(11, 99))
    while frst in ['20', '23', '25', '26', '29', '30', '36', '39', '40', '50', '52', '56', '57', '58', '59', '60', '70', '72', '78', '80', '90']:
        frst = str(random.randint(11, 99))

    scnd = str(random.randint(8000, 9998))
    while scnd in ['8888']:
        scnd = str(random.randint(8000, 9998))

    thrd = (str(random.randint(1, 9998)).zfill(4))
    while thrd in ['1111', '2222', '3333', '4444', '5555', '6666', '7777', '8888']:
        thrd = (str(random.randint(1, 9998)).zfill(4))

    return '=\"+55 ({}) 9{}-{}\"'.format(frst, scnd, thrd)

n = int(input("Enter Value of n: "))

for i in range(0, n):
    print(random_phone_num_generator())