package ch.adesso.demo.server;

import ch.adesso.demo.model.PrimesDto;
import ch.adesso.demo.service.SieveOfAtkin;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Server {

    private SieveOfAtkin sieveOfAtkin;

    public Server(SieveOfAtkin sieveOfAtkin) {
        this.sieveOfAtkin = sieveOfAtkin;
    }

    @GetMapping
    public String read() {
        return "Hello from JVM";
    }

    @GetMapping("/primes")    
    public PrimesDto primes(@RequestParam(value = "limit", required = false, defaultValue = "100") int limit) {
        return new PrimesDto(sieveOfAtkin.calculate(limit));        
    }
}
