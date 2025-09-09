def problem125B() -> None:
    in_xml = input()
    tags = [tag + ">" for tag in in_xml.split('>')[:-1]]
    stack = []
    for tag in tags:
        if tag[1] == "/":  # closing tag
            letter = tag[2]
            if letter == stack[-1][1]:  # matching opening tag
                stack.pop()
                print((len(stack) * 2) * " " + tag)
            else:
                print((len(stack) * 2) * " " + tag)
                stack.append(tag)

        else:  # opening tag
            letter = tag[1]
            print((len(stack) * 2) * " " + tag)
            stack.append(tag)
        
problem125B()