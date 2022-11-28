typedef long long L;
L exponentiation_by_square(L base, L index, L modulus) {// assert modulus is a prime, and gcd(base, modulus) == 1
	L result = 1;
	index %= modulus - 1; // phi(modulus) == modulus - 1
	index += index < 0 ? (modulus - 1) : 0; 
	while (index) {
		if (index & 1) result = multiply(result, base, modulus);
		if (index >>= 1) base = multiply(base, base, modulus);
	}
	return result;
}
