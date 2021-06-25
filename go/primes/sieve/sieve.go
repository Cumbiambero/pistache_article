package sieve

import (
	"math"
)

func Calculate(limit int) []int {
	sieve := createSieve(limit)
	return extractNumbers(limit, sieve)
}

func createSieve(limit int) []bool {
	sieve := make([]bool, int(math.Max(4, float64(limit+1))))
	for i := 0; i < limit; i++ {
		sieve[i] = false
	}
	sieve[2] = true
	sieve[3] = true
	sieve[4] = false

	for x := 1; x*x < limit; x++ {
		for y := 1; y*y < limit; y++ {
			n := (4 * x * x) + (y * y)
			if n <= limit && (n%12 == 1 || n%12 == 5) {
				sieve[n] = !sieve[n]
			}
			n = (3 * x * x) + (y * y)
			if n <= limit && n%12 == 7 {
				sieve[n] = !sieve[n]
			}
			n = (3 * x * x) - (y * y)
			if x > y && n <= limit && n%12 == 11 {
				sieve[n] = !sieve[n]
			}
		}
	}

	for r := 5; r*r < limit; r++ {
		if sieve[r] {
			for i := r * r; i < limit; i += r * r {
				sieve[i] = false
			}
		}
	}
	return sieve
}

func extractNumbers(limit int, sieve []bool) []int {
	var result []int
	for a := 2; a < limit; a++ {
		if sieve[a] {
			result = append(result, a)
		}
	}
	return result
}
