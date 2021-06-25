FROM openjdk:12-alpine
VOLUME /tmp
ARG JAR_FILE
COPY target/*.jar app.jar
ENTRYPOINT ["java","-jar","/app.jar"]
EXPOSE 8081 8081