all:
	cd B1 && docker build -t b1_out .
	# docker run --rm b1_out ./build/exampleB1