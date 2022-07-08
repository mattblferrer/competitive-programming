from itertools import product


# returns the XOR of an encrypted message and a key
def xor_string(message, key):
    cipher = ""

    # iterate through every character
    for i in range(len(message)):
        message_ord = message[i]
        key_ord = ord(key[i % len(key)])

        # xor and append to string
        xor_ord = message_ord ^ key_ord
        cipher += chr(xor_ord)

    return cipher


# read from file
file1 = open("p059_cipher.txt", "r")
enc_message = [int(num) for num in file1.readline().split(",")]

# declare variables
possible_keys = [''.join(key) for key in list(product("abcdefghijklmnopqrstuvwxyz", repeat=3))]
maximumWords = 0
maximumMsg = ""

# main loop
for key in possible_keys:
    dec_message = xor_string(enc_message, key)  # decrypt message

    # check message for number of words
    dec_message = dec_message.split(" ")
    if len(dec_message) > maximumWords:  # assumes that the message has the most words, or the least entropy
        maximumWords = len(dec_message)
        maximumMsg = dec_message

# calculate sum of ASCII values in message
maximumMsg = ' '.join(word for word in maximumMsg)
characterSum = sum(ord(char) for char in maximumMsg)

print("Sum of ASCII values:", characterSum)
print("Message: ", maximumMsg)
