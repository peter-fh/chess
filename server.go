package main

import (
	"bufio"
	"fmt"
	"net/http"
	"os"
)

const logVersion = 1;

type Config struct {
    Version     int     `json:"version"`
    Fen		string  `json:"fen"`
    Moves	bool    `json:"moves"` 
}
func logHandler(writer http.ResponseWriter, req* http.Request) {
	for name, value := range req.Header {
		fmt.Printf("%s: %s\n", name, value)
	}	
	fmt.Println("\n\nBody:")

	
	scanner := bufio.NewScanner(req.Body)
	log_text := ""
	for scanner.Scan(){
		log_text += scanner.Text()
	}
	log_text += "\n"
	fmt.Printf("%s", log_text)

	log_file, err := os.OpenFile("log.txt", os.O_RDWR | os.O_APPEND, os.ModePerm)
	if err != nil {
		fmt.Println(err)
	}

	_, err = fmt.Fprintf(log_file, log_text)
	if err != nil {
		fmt.Println(err)
	}

	fmt.Fprintln(writer, "success!")
}

func main(){

	port := ":8080"
	http.Handle("/", http.FileServer(http.Dir("./chess")))
	http.HandleFunc("/log", logHandler)
	fmt.Printf("Started server at port=%s\n", port)
	err := http.ListenAndServe(port, nil);
	if err != nil{
		panic(err)
	}
}
