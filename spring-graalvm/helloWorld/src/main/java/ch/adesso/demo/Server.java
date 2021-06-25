package ch.adesso.demo;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class Server {

    @GetMapping
    public String read() {
        return "Hello from GraalVM";
    }
}
