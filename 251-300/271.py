from sympy.ntheory.residue_ntheory import nthroot_mod
print(sum(nthroot_mod(1, 3, 13082761331670030)) - 1)  # 1 is excluded in bounds
