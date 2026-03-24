package main

import (
	"encoding/json"
	"log"
	"net/http"
	"os"
)

type response struct {
	Service string `json:"service"`
	Message string `json:"message"`
}

func main() {
	addr := ":8080"
	if p := os.Getenv("PORT"); p != "" {
		addr = ":" + p
	}

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		_ = json.NewEncoder(w).Encode(response{
			Service: "go",
			Message: "final hop in rust -> cpp -> go chain",
		})
	})

	http.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
		w.WriteHeader(http.StatusOK)
		_, _ = w.Write([]byte("ok"))
	})

	log.Printf("go server listening on %s", addr)
	log.Fatal(http.ListenAndServe(addr, nil))
}
