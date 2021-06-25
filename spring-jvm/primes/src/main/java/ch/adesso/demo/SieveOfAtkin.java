package ch.adesso.demo.service;

import java.util.HashSet;
import java.util.Set;

import org.springframework.stereotype.Service;

@Service
public class SieveOfAtkin {
    public Set<Integer> calculate (int limit) { 
        boolean[] sieve = createSieve(limit); 
        return prepareResult(limit, sieve);
    }

    private boolean[] createSieve(int limit) {
        boolean sieve[] = new boolean[Math.max(4, limit + 1)];
        sieve[2] = true;
        sieve[3] = true;
    
        for (int x = 1; x * x < limit; ++x) { 
            for (int y = 1; y * y < limit; ++y) {   
                int n = (4 * x * x) + (y * y); 
                if (n <= limit && (n % 12 == 1 || n % 12 == 5)) {
                    sieve[n] ^= true; 
                }
  
                n = (3 * x * x) + (y * y); 
                if (n <= limit && n % 12 == 7) {
                    sieve[n] ^= true; 
                }
  
                n = (3 * x * x) - (y * y); 
                if (x > y && n <= limit && n % 12 == 11) {
                    sieve[n] ^= true; 
                }
            } 
        } 

        for (int r = 5; r * r < limit; ++r) { 
            if (sieve[r]) { 
                for (int i = r * r; i < limit; 
                     i += r * r) 
                    sieve[i] = false; 
            } 
        }
        return sieve;
    }    

    private Set<Integer> prepareResult(int limit, boolean[] sieve) {
        Set<Integer> result = new HashSet<>();
        for (int a = 2; a < limit; ++a) {
            if (sieve[a]) {
                result.add(a);
            }
        }
        return result;
    }
}