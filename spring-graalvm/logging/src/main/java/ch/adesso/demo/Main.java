package ch.adesso.demo;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication(proxyBeanMethods = false)
public class Main {

    public static void main(String[] args) {
        SpringApplication.run(Main.class, args);
    }
}
