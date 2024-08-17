package main;

import (
	"fmt"
	"net/http"
)


func main(){

	port := ":8080"
	http.Handle("/", http.FileServer(http.Dir("./chess")))
	fmt.Printf("Started server at port=%s\n", port)
	err := http.ListenAndServe(port, nil);
	if err != nil{
		panic(err)
	}
}
