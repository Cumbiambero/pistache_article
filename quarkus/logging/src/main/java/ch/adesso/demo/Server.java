package ch.adesso.demo;

import javax.inject.Inject;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.Set;
import org.jboss.logging.Logger;

@Path("/")
@Produces(MediaType.APPLICATION_JSON)
public class Server {

    @Inject
    Logger log; 

    @Inject
    SieveOfAtkin sieveOfAtkin;

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String hello() {
        log.info("Processed / request");
        return "Hello from Quarkus";
    }

    @GET
    @Path("/primes")
    public PrimesDto primes(@DefaultValue("100") @QueryParam("limit") int limit) {
        Set<Integer> calculate = sieveOfAtkin.calculate(limit);
        log.info("Processed /primes request");
        return new PrimesDto(calculate);
    }
}
