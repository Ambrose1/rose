package main

import "sync"

var once sync.Once

type Singleton struct {

}

var instance *Singleton

func GetInstance() *Singleton {
	once.Do(func() {
		instance = &Singleton {

		}
	})
	return instance
}