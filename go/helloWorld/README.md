# Go Demo
## Run
`go run main.go`
## Building
```
pack build go-gin-sample \
           --buildpack gcr.io/paketo-buildpacks/go \
           --builder paketobuildpacks/builder:tiny
```
## Running
`docker run --interactive --tty --env PORT=8080 --publish 8080:8080 godemo`
