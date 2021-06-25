FROM alpine:latest
COPY . sources

ENV GIN_MODE release

RUN apk -U upgrade && apk add --no-cache go && \
    cd sources && go mod download && go build -o /usr/bin/godemo main.go && cd - && \
    rm -r sources && \
    apk del --purge go

CMD ["godemo"]