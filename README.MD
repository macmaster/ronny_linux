# ronny_linux 
my very own operating system.

## Cross GNU Toolkit  
Head over to the releases section and grab the toolkit.  
Download the cross.tar.gz file.  
```bash
gunzip cross.tar.gz
tar xf cross.tar
rm cross.tar
mv cross /usr
export PATH="/usr/cross/bin:$PATH"
```


## Building
build: `make ronny`
clean: `make clean`
