const express = require('express');
const app = express();
const PORT = 3000;

// resource
const books = [
	{id:1,title:"a book", author:'jim'},
	{id:2,title:"the another book", author:'jim'},
	{id:3,title:"book", author:'jim'}
];

app.get('/books',(req, res)=>{
	res.json(books);
});

app.get('/singlebook/:id',(req,res)=>{
	const id = Number(req.params.id)
	const book = books.find(book => book.id === id);
	if (book) {
		res.json(book);
	} else {
		res.status(404).send("book not found")
	}
});

app.listen(PORT, ()=>{
	console.log("server is listening on port ${PORT}")
});