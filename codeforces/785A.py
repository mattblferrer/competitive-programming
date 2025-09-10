def problem785A() -> int:
    test_cases = int(input())
    faces = 0

    for _ in range(test_cases):
        polyhedron = input()
        if polyhedron == "Tetrahedron":
            faces += 4
        elif polyhedron == "Cube":
            faces += 6
        elif polyhedron == "Octahedron":
            faces += 8
        elif polyhedron == "Dodecahedron":
            faces += 12
        elif polyhedron == "Icosahedron":
            faces += 20

    return faces

print(problem785A())