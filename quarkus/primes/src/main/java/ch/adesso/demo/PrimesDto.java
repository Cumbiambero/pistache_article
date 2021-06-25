package ch.adesso.demo;

import java.util.Set;

public class PrimesDto {
    private final int count;
    private final Set<Integer> primes;

    public PrimesDto(Set<Integer> primes) {
        this.primes = primes;
        this.count = primes.size();
    }

    public Set<Integer> getPrimes() {
        return primes;
    }

    public int getCount() {
        return count;
    }    
}
