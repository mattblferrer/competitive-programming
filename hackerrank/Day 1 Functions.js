
/*
 * Create the function factorial here
 */
function factorial(n) {
    let f = 1;
    let m = 2;
    while (m <= n) {
        f = f * m;
        m += 1
    }
    return f;
}
