all:
	cd detector_test && docker build -t test .
	docker run --rm test ./d_test