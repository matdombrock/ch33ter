## Deps
### macOS
```bash
xcode-select --install
```
### Linux (Debian based)
```bash
sudo apt update
sudo apt install build-essential
```

## Building
To build just run:
```bash
make
```

The built files will be in:
```
./out
```

## Cross Compilation
### Install Deps
Cross compilations is possible from macOS.
```
# Windows
brew install mingw-w64
# Linux
brew install FiloSottile/musl-cross/musl-cross
```
### Building
```
# Windows
make cross-win
# Linux
make cross-lin
```