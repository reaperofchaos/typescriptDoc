make clean
make all
rm -rf comic_form/TypescriptDocumentGenerator
mv TypescriptDocumentGenerator comic_form/TypescriptDocumentGenerator
cd comic_form
./TypescriptDocumentGenerator
cd ..