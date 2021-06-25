# Hello World in Go using gin
## Develop
`go run main.go`

## Building
```
pack build godemo \
           --buildpack gcr.io/paketo-buildpacks/go \
           --builder paketobuildpacks/builder:tiny
```

## Running
`docker run --interactive --tty --env PORT=8080 --publish 8085:8085 godemo`
