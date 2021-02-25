.PHONY: B1 sauna

all:
	@echo "Choose B1 or sauna"

B1:
	cd B1 && docker build -t b1_out .
	# --------------------------------------- #
	# Open a new terminal window and open ssh #
	# --------------------------------------- #
	docker run --rm -i -p 55555:22 -t b1_out bash -l

sauna: 
	cd sauna && docker build -t sauna_out .
	# --------------------------------------- #
	# Open a new terminal window and open ssh #
	# --------------------------------------- #
	docker run --rm -i -p 55555:22 -t sauna_out bash -l

compile:
	cd B1 && docker build -t b1_out .
	cd sauna && docker build -t sauna_out .
