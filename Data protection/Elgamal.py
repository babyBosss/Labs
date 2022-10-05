#!/usr/bin/env python
import random
from math import pow

# Схема Эль-Гамаля (Elgamal) - криптосистема с открытым ключом,
# основанная на трудности вычисления дискретных логарифмов в конечном поле.

# Генерация ключей
# 1.	Генерируется случайное простое число p.
# 2.	Выбирается целое число g — первообразный корень p.
# 3.	Выбирается случайное целое число x такое, что 1 < x < p-1 .
# 4.	Вычисляется y = gx mod p.
# 5.	Открытым ключом является (y,g,p), закрытым ключом — число x.
# Шифрование
# Сообщение msg должно быть меньше числа p. Сообщение шифруется следующим образом:
# 1.	Выбирается сессионный ключ — случайное целое число, взаимно простое с (p-1), k  такое, что 1 < k < p-1.
# 2.	Вычисляются числа a = gk mod p и b = yk msg mod p.
# 3.	Пара чисел (a,b) является шифротекстом.

a = random.randint(0,10)

def encrypt(msg, q, h, g):
    en_msg = []
    k = gen_key(q)  # Приватный ключ отправителя
    s = power(h, k, q)
    p = power(g, k, q)
    for i in range(0, len(msg)):
        en_msg.append(msg[i])
    for i in range(0, len(en_msg)):
        en_msg[i] = s * ord(en_msg[i])
    return en_msg, p


def decrypt(en_msg, p, key, q):
    dr_msg = []
    h = power(p, key, q)
    for i in range(0, len(en_msg)):
        dr_msg.append(chr(int(en_msg[i]/h)))
    return dr_msg


def gcd(a, b):
    if a < b:
        return gcd(b, a)
    elif a % b == 0:
        return b
    else:
        return gcd(b, a % b)


def gen_key(q):
    key = random.randint(pow(10, 20), q)
    while gcd(q, key) != 1:
        key = random.randint(pow(10, 20), q)
    return key


def power(a, b, c):
    x = 1
    y = a
    while b > 0:
        if b % 2 != 0:
            x = (x * y) % c;
        y = (y * y) % c
        b = int(b / 2)
    return x % c



msg = str(input("Введите сообщение: "))
q = random.randint(pow(10, 20), pow(10, 50))
g = random.randint(2, q)
key = gen_key(q)  # Приватный ключ получателя
h = power(g, key, q)
en_msg, p = encrypt(msg, q, h, g)
dec_msg = ''.join(decrypt(en_msg, p, key, q))
print("Дешифрованное сообщение:", dec_msg)

