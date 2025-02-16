#!/bin/python3
# Zajisteni zakladni kompatibility IFJ19->Python3 @ Merlin
def inputs():
  try:
    return input()
  except Exception:
    return None

def inputi():
  try:
    line = input()
    if line.count("0x") == 1:   # hexadecimalni format
      return int(line, 16)
    else:
      return int(line)
  except Exception:
    return None

def inputf():
  try:
    line = input()
    if line.count("p") == 1:    # hexadecimalni format
      return float.fromhex(line)
    else:
      return float(line)
  except Exception:
    return None

__len = len    
def len(s):
  try:
    return __len(s)
  except Exception:
    return None

def substr(s, i, n):
  try:
    if i < 0 or i > __len(s) or n < 0:
      return None
    return s[i:i+n]
  except Exception:
    return None

__ord = ord
def ord(s, i):
  try:
    return __ord(s[i])
  except Exception:
    return None

#def chr(i):
#  chr(i)

__print = print
def print(*args):
  length = __len(args)
  for i, arg in enumerate(args):
    if arg.__class__ == float:
      __print(arg.hex(), end='')
    else:
      __print(arg, end='')
    if i < length - 1:
      __print(' ', end='')
  __print('\n', end='')
  return None

# Zde bude nasledovat program jazyka IFJ19
""" Program 3: Prace s retezci a vestavenymi funkcemi """
s1 = 'Toto je nejaky text'
s2 = s1 + ', ktery jeste trochu obohatime'
print(s1, '\n', s2)
s1len = len(s1)
s1len = s1len - 4
s1 = substr(s2, s1len, 4)
s1len = s1len + 1 #korekce indexu znaku na poradi znaku 
print('4 znaky od', s1len, '. znaku v "', s2, '\":', s1)
print('Zadejte serazenou posloupnost vsech malych pismen a-h, ')
print('pricemz se pismena nesmeji v posloupnosti opakovat: ')
s1 = inputs()
if s1 != None:
 while s1 != 'abcdefgh':
  print('Spatne zadana posloupnost, zkuste znovu: ')
  s1 =inputs()
else: #nezadan zadny vstup (EOF)
 pass
