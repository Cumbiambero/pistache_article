package main

import (
	"adesso.ch/demo/sieve"
	"github.com/gin-gonic/gin"
	"net/http"
	"strconv"
)

func main() {
	r := gin.Default()
	r.GET("/", func(c *gin.Context) {
        c.String(http.StatusOK, "Hello from Go")
    })
	r.GET("/primes", func(c *gin.Context) {
		limit, _ := strconv.ParseInt(c.DefaultQuery("limit", "100"), 10, 32)
		result := sieve.Calculate(int(limit))

		c.JSON(http.StatusOK, gin.H{
			"count": len(result),
			"primes": result,
		})
	})
	_ = r.Run(":8085")
}