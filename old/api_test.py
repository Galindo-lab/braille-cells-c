import ctypes 


# https://stackoverflow.com/questions/61294630/ctypes-passing-a-string-as-a-pointer-from-python-to-c

my_functions = ctypes.CDLL("./libtest.so")

arr_a = ctypes.create_string_buffer(255, size=None)

arr_b = ctypes.create_string_buffer(255, size=None)
arr_b.value = b"Hola Mundo6"

my_functions.str_to_braille(
    arr_a,
    arr_b
)

print("C dice: ", end="")
my_functions.main()

print("Python dice: Hola Mundo6")
for byte in arr_a:
    foo = int.from_bytes(byte, "little")
    if foo != 0:
        print(foo)
    else:
        break


