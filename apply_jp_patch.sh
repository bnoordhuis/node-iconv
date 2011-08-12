cd ./deps/libiconv-1.13.1/;
gzip -dc ../libiconv-1.13-ja-1.patch.gz | patch -p1;
./configure --disable-shared --enable-static --enable-relocatable --enable-extra-encodings;
make;
cd ../../;
make;
