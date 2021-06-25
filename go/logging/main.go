package main

import (
	"adesso.ch/demo/sieve"
	"github.com/gin-gonic/gin"
	log "github.com/sirupsen/logrus"
	"net/http"
	"os"
	"strconv"
	"time"
)

func initLogging() {
	log.SetFormatter(&log.TextFormatter{
		DisableColors: false,
		FullTimestamp: true,
		TimestampFormat : "2006-01-02T15:04:05.000",
		FieldMap: log.FieldMap{
			log.FieldKeyTime:  "ts",
			log.FieldKeyLevel: "lvl",
			log.FieldKeyMsg:   "msg"}})
	log.SetOutput(os.Stdout)
}

func main() {
	start := time.Now()
	initLogging()
	r := gin.New()
	r.GET("/", func(c *gin.Context) {
        c.String(http.StatusOK, "Hello from Go")
		log.WithFields(log.Fields{"src": "main"}).Info("Processed / request")
    })
	r.GET("/primes", func(c *gin.Context) {
		limit, _ := strconv.ParseInt(c.DefaultQuery("limit", "100"), 10, 32)
		result := sieve.Calculate(int(limit))
		c.JSON(http.StatusOK, gin.H{
			"count": len(result),
			"primes": result,
		})
		log.WithFields(log.Fields{"src": "main"}).Info("Processed /primes request")
	})
	elapsed := time.Since(start)
    log.Info("Startup took ", elapsed)
	_ = r.Run(":8085")
}