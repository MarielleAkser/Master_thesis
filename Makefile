all:
	cd detector_test && docker build -t test .
	docker run --rm -it test ./d_test