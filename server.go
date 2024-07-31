package main;

import (
	"fmt"
	"net/http"
)


func main(){

	fmt.Println("starting server")
	http.Handle("/", http.FileServer(http.Dir("./chess")))
	err := http.ListenAndServe(":8085", nil);
	if err != nil{
		panic(err)
	}
}
