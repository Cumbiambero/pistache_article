# Hello World with Quarkus
- JDK 11
- Quarkus
- JVM or GraalVM

## Building the application

> mvn install

### Live coding with Quarkus

The Maven Quarkus plugin provides a development mode that supports
live coding. To try this out:

> mvn quarkus:dev

### Run Quarkus in JVM mode

When you're done iterating in developer mode, you can run the application as a
conventional jar file.

First compile it:

> mvn install

Then run it:

> java -jar ./target/quarkus-app/quarkus-run.jar

Have a look at how fast it boots, or measure the total native memory consumption.

### Run Quarkus as a native executable

Use the `native` profile to compile a native executable:

> mvn install -Pnative

Compile the native executable via buildpack:

> mvn package -Pnative -Dquarkus.native.container-build=true

After getting a cup of coffee, you'll be able to run this executable directly:

> ./target/quarkusdemo-1.0.0-SNAPSHOT-runner

## Containerize
### JVM mode
> docker build -f src/main/docker/Dockerfile.jvm -t quarkusdemo:jvm-latest .

### Docker (native)
> docker build -f src/main/docker/Dockerfile.native -t quarkusdemo:latest .

### With Mandrel
**(!) Work in progress.** The command does not work, yet.
```
mvn package -Pnative \
            -Dquarkus.native.container-build=true \ 
            -Dquarkus.native.builder-image=quay.io/quarkus/ubi-quarkus-mandrel:{mandrel-flavor}
```
