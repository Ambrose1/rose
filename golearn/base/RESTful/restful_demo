package main

import (
	"net/http"

	"github.com/gin-gonic/gin"
)

type Book struct {
	Id int `json:"id"`
	Title string `json:"title"`
	Author string `json:"author`
}

var book []Book

func main(){
	r := gin.Default()

		// 初始化一些书籍
	books = []Book{
		{ID: 1, Title: "JavaScript: The Good Parts", Author: "Douglas Crockford"},
		{ID: 2, Title: "Clean Code", Author: "Robert C. Martin"},
		{ID: 3, Title: "Code Complete", Author: "Steve McConnell"},
	}

	r.GET("/books", func(c *gin.Context){
		c.JSON(http.StatusOK, books)
	})


	// 删除书籍
	r.DELETE("/books/:id", func(c *gin.Context) {
		id, err := strconv.Atoi(c.Param("id"))
		if err != nil {
			c.AbortWithStatusJSON(http.StatusBadRequest, gin.H{"error": "Invalid book ID"})
			return
		}
		for i, book := range books {
			if book.ID == id {
				books = append(books[:i], books[i+1:]...)
				c.Status(http.StatusNoContent)
				return
			}
		}
		c.AbortWithStatusJSON(http.StatusNotFound, gin.H{"error": "Book not found"})
	})


	r.Run(":8080")
}