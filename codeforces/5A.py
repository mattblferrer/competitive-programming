import sys

def problem5A() -> None:
    traffic = 0
    participants = set()

    while True:
        line = sys.stdin.readline().strip()
        if len(line) == 0:
            break
        if line[0] == "+":  # add participant
            participants.add(line[1:])
        elif line[0] == "-":  # remove participant
            participants.remove(line[1:])
        else:
            message = line.split(":")[1]
            traffic += len(message) * len(participants)

    print(traffic)

problem5A()