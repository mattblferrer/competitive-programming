from itertools import product


# returns the XOR of an encrypted message and a key
def xor_string(message: str, key: str) -> str:
    cipher = ""

    # iterate through every character
    for i, message_ord in enumerate(message):
        key_ord = ord(key[i % len(key)])
        xor_ord = message_ord ^ key_ord  # xor and append to string
        cipher += chr(xor_ord)

    return cipher


def main():
    # read from file
    with open("p059_cipher.txt", "r") as f:
        enc_message = [int(num) for num in f.readline().split(",")]

    # declare variables
    possible_keys = [''.join(key) for key in list(product(
        "abcdefghijklmnopqrstuvwxyz", repeat=3))]
    maximum_words = 0
    maximum_msg = ""

    # main loop
    for key in possible_keys:
        dec_message = xor_string(enc_message, key).split(" ") # decrypt message

        # check message for number of words (assumes that the message has the 
        # most words, or the least entropy)
        if len(dec_message) > maximum_words:
            maximum_words = len(dec_message)
            maximum_msg = dec_message

    # calculate sum of ASCII values in message
    maximum_msg = ' '.join(word for word in maximum_msg)
    character_sum = sum(ord(char) for char in maximum_msg)

    print("Sum of ASCII values:", character_sum)
    print("Message: ", maximum_msg)


if __name__ == "__main__":
    main()
