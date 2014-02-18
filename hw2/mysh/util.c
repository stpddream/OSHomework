/**
 * Mod function that computes the "positive" remainder for negative n1
 * @param n1
 * @param n2 has to be positive
 * @return 
 */
int mod(int n1, int n2) {              
    int res = n1 % n2;
    return (res < 0) ? res + n2 : res;        
}