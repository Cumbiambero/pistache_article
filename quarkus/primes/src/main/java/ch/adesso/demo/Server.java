package ch.adesso.demo;

import javax.inject.Inject;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import java.util.Set;

@Path("/")
@Produces(MediaType.APPLICATION_JSON)
public class Server {
    @Inject
    SieveOfAtkin sieveOfAtkin;

    @GET
    @Produces(MediaType.TEXT_PLAIN)
    public String hello() {
        return "Hello from Quarkus";
    }

    @GET
    @Path("/primes")
    public PrimesDto primes(@DefaultValue("100") @QueryParam("limit") int limit) {
        Set<Integer> calculate = sieveOfAtkin.calculate(limit);
        return new PrimesDto(calculate);
    }
}
