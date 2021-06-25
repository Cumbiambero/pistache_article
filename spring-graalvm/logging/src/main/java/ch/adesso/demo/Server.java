package ch.adesso.demo.server;

import ch.adesso.demo.model.PrimesDto;
import ch.adesso.demo.service.SieveOfAtkin;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Server {
    private static final Logger LOG = LoggerFactory.getLogger(Server.class);

    private SieveOfAtkin sieveOfAtkin;

    public Server(SieveOfAtkin sieveOfAtkin) {
        this.sieveOfAtkin = sieveOfAtkin;
    }

    @GetMapping
    public String read() {
        LOG.info("Processed / request");
        return "Hello from GraalVM";
    }

    @GetMapping("/primes")    
    public PrimesDto primes(@RequestParam(value = "limit", required = false, defaultValue = "100") int limit) {
        LOG.info("Processed /primes request");
        return new PrimesDto(sieveOfAtkin.calculate(limit));
    }
}
