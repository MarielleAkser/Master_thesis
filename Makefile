all:
	cd B1 && docker build -t b1_out .
	# --------------------------------------- #
	# Open a new terminal window and open ssh #
	# --------------------------------------- #
	docker run --rm -i -p 55555:22 -t b1_out bash -l
	