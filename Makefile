all: build


build:
	cmake --build build


configure:
	cmake -S. -Bbuild

clean:
	rm -rf build

dump:
	coredumpctl dump --output core.dump


