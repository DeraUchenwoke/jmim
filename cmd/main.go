package main

import (
	"fmt"
	"log"
	"os"

	cli "github.com/urfave/cli/v2"
)

// Using examples to start with: https://github.com/urfave/cli/tree/main/docs/v2/examples
func main() {
	fmt.Println("Hello world")
	app := &cli.App{
		Name:  "greet",
		Usage: "fight the loneliness!",
		Action: func(*cli.Context) error {
			fmt.Println("Hello friend!")
			return nil
		},
	}

	if err := app.Run(os.Args); err != nil {
		log.Fatal(err)
	}

	// Very rough plan: 1) Create JMIM function with CSV files 2) Create CLI tool to use it
}
