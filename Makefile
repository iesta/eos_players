 CC = eosiocpp
 CT = Players
 OWNER = bob

default: all

all: build publish

build: clean wast abi

wast:
	$(CC) -o $(CT).wast $(CT).cpp

abi:
	$(CC) -g $(CT).abi $(CT).cpp

publish: 
	cleos set contract $(OWNER) ../$(CT)/

deploy: publish

clean:
	-rm -f $(CT).wasm $(CT).wast $(CT).abi

