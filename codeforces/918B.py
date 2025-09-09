def problem918B() -> None:
    n, m = map(int, input().split(' '))
    server_names = {}  # ip: name pairs

    for _ in range(n):
        name, ip = input().split()
        server_names[ip] = name

    for _ in range(m):
        command, ip = input().split()  # ip includes ;
        print(f"{command} {ip} #{server_names[ip[:-1]]}")  

problem918B()