build: clear
	gcc src/main.c -o build/app -O3 -march=native -Wall

run: ./build/app
	./build/app

zip: clear
	zip -r build/files.zip .

clear:
	rm -rf ./build/*

